#include <iostream>
#include <cmath>
#include <android/log.h>

 #if (defined __ARM_NEON) || (defined __ARM_NEON__)
    #define OPEN_NEON
 #endif

#ifdef OPEN_NEON
    #include "neon_mathfun.h"
#endif

#define  LOG_TAG_MY    "int8LstmModel:"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG_MY,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG_MY,__VA_ARGS__)

#ifdef OPEN_NEON

        void multiply_(float* ptr , float* ptr1 , float* outptr, int count) {
            if(!ptr|| !ptr1 || count <1)
                return;
            //double s = gemmlowp::real_time_in_seconds();
            int nn = count >> 2;
            int remain = count - (nn << 2);

            #if __aarch64__
                        if (nn > 0)
                        {
                        asm volatile(
                            "0:                               \n"
                            "prfm       pldl1keep, [%1, #128] \n"
                            "prfm       pldl1keep, [%2, #128] \n"
                            "ld1        {v0.4s}, [%1], #16    \n"
                            "ld1        {v1.4s}, [%2], #16    \n"
                            "fmul       v0.4s, v0.4s, v1.4s   \n"
                            "subs       %w0, %w0, #1          \n"
                            "st1        {v0.4s}, [%3], #16    \n"
                            "bne        0b                    \n"
                            : "=r"(nn),     // %0
                              "=r"(ptr),    // %1
                              "=r"(ptr1),   // %2
                              "=r"(outptr)  // %3
                            : "0"(nn),
                              "1"(ptr),
                              "2"(ptr1),
                              "3"(outptr)
                            : "cc", "memory", "v0", "v1"
                        );
                        }
            #else
                        if (nn > 0)
                        {
                        asm volatile(
                            "0:                             \n"
                            "pld        [%1, #128]          \n"
                            "pld        [%2, #128]          \n"
                            "vld1.f32   {d0-d1}, [%1 :128]! \n"
                            "vld1.f32   {d2-d3}, [%2 :128]! \n"
                            "vmul.f32   q0, q0, q1          \n"
                            "subs       %0, #1              \n"
                            "vst1.f32   {d0-d1}, [%3 :128]! \n"
                            "bne        0b                  \n"
                            : "=r"(nn),     // %0
                              "=r"(ptr),    // %1
                              "=r"(ptr1),   // %2
                              "=r"(outptr)  // %3
                            : "0"(nn),
                              "1"(ptr),
                              "2"(ptr1),
                              "3"(outptr)
                            : "cc", "memory", "q0", "q1"
                        );
                        }
            #endif // __aarch64__
            for (; remain>0; remain--)
            {
                *outptr = *ptr * *ptr1;
                ptr++;
                ptr1++;
                outptr++;
             }
        	//double e = gemmlowp::real_time_in_seconds();
        	//LOGE("multiply time: %d element wise multiplication %.3g ms\n",count,  (e-s)*1000);
        }

          void multiply(float* ptr , float* ptr1 , float* outptr, int count) {
               if(!ptr|| !ptr1 || count <1)
                   return;
               double s = gemmlowp::real_time_in_seconds();
               int nn = count >> 2;
               int remain = count - (nn << 2);
               float32x4_t _o;
               for (; nn>0; nn--)
               {
                    float32x4_t _a = vld1q_f32(ptr);
                    float32x4_t _b = vld1q_f32(ptr1);
                    //float32x4_t _o = vld1q_f32(outptr);
                    _o = vmulq_f32(_a, _b);
                    vst1q_f32(outptr, _o);
                    ptr += 4;
                    ptr1 +=4;
                    outptr +=4;
               }
               for (; remain>0; remain--)
               {
                    *outptr = *ptr * *ptr1;
                    ptr++;
                    ptr1++;
                    outptr++;
               }
               double e = gemmlowp::real_time_in_seconds();
               LOGE("multiply time: %d element wise multiplication %.3g ms\n",count,  (e-s)*1000);
          }


    void sigmoid(float *ptr, int count)
    {
       if(!ptr|| count <1)
        return;
       int nn = count >> 2;
       int remain = count - (nn << 2);

       float32x4_t _one = vdupq_n_f32(1.f);
        for (; nn>0; nn--)
        {
            float32x4_t _p = vld1q_f32(ptr);
            _p = vnegq_f32(_p);
            _p = exp_ps(_p);
            _p = vaddq_f32(_p, _one);
            float32x4_t _outp = vrecpeq_f32(_p);
            _outp = vmulq_f32(vrecpsq_f32(_p, _outp), _outp);
            vst1q_f32(ptr, _outp);
            ptr += 4;
        }
        for (; remain>0; remain--)
        {
           *ptr = 1.f / (1.f + ::std::exp(-*ptr));
            ptr++;
         }
    }

    /*
      value = exp( value - global max value )
      sum all value
      value = value / sum
    */
	void softmax(float* ptr, int count) {
	    if(!ptr|| count <1)
                return;

        float dMax = -FLT_MAX;
		float* start = ptr;
        // max
        for (int i=0; i< count; i++)
        {
           dMax = ::std::max(dMax, ptr[i]);
         }

		//  value = exp( value - global max value )
		int nn = count >> 2;
        int remain = count - (nn << 2);

        for (; nn>0; nn--)
        {
            float32x4_t _p = vld1q_f32(ptr);
            float32x4_t _max = vdupq_n_f32(dMax);
            _p = exp_ps(vsubq_f32(_p, _max));
            vst1q_f32(ptr, _p);
            ptr += 4;
         }
        for (; remain>0; remain--)
        {
           *ptr = ::std::exp(*ptr - dMax);
            ptr++;
         }

        //   sum all value
        ptr = start;
        nn = count >> 2;
        remain = count - (nn << 2);
       float32x4_t sum_vec = vdupq_n_f32(0.0);
       for (; nn > 0; nn--)
       {
           float32x4_t data_vec = vld1q_f32(ptr);
           sum_vec = vaddq_f32(sum_vec, data_vec);
           ptr+=4;
       }
       // 将累加结果寄存器中的所有元素相加得到最终累加值
       float sum_all = vgetq_lane_f32(sum_vec, 0) + vgetq_lane_f32(sum_vec, 1) + \
        vgetq_lane_f32(sum_vec, 2)+vgetq_lane_f32(sum_vec, 3);

        for (; remain>0; remain--)
        {
            sum_all += *ptr;
             ptr++;
         }
         //  value = value / sum
         ptr = start;
         nn = count >> 2;
         remain = count - (nn << 2);
         for (; nn>0; nn--)
         {
            float32x4_t _p = vld1q_f32(ptr);
            float32x4_t _sum = vdupq_n_f32(sum_all);
        #if __aarch64__
             _p = vdivq_f32(_p, _sum);
        #else
             _p = div_ps(_p, _sum);
        #endif // __aarch64__
             vst1q_f32(ptr, _p);
             ptr += 4;
          }

        for (; remain>0; remain--)
        {
            *ptr /= sum_all;
             ptr++;
         }
	}
	
	
	
	/*
   TanH = (e^x - e^-x) / (e^x + e^-x)
   TanH = (e^x - e^-x)(e^x) / (e^x + e^-x)(e^x)
   TanH = (e^2x - 1) / (e^2x + 1)
   */
    void tanh(float *ptr, float *outptr, int count) {
        if (!ptr || !outptr || count <1)
            return;
        int nn = count >> 2;
        int remain = count - (nn << 2);
               float32x4_t _one = vdupq_n_f32(1.f);
               float32x4_t _scale = vdupq_n_f32(2.f);
                for (; nn>0; nn--)
                {
                  		float32x4_t _p = vld1q_f32(ptr);
                  		//float32x4_t _negp = vnegq_f32(_p); // -x
                  		_p = vmulq_f32(_p, _scale); // 2x
                  		_p = exp_ps(_p);// e_2x
                  		//_negp = exp_ps(_negp);// e_-x
                  		float32x4_t _fenZi = vsubq_f32(_p, _one);
                  		float32x4_t _fenMu = vaddq_f32(_p, _one);
                  #if __aarch64__
                  			_p = vdivq_f32(_fenZi, _fenMu);
                  #else
                  			_p = div_ps(_fenZi, _fenMu);
                  #endif // __aarch64__
                  		vst1q_f32(outptr, _p);
                  		ptr += 4;
                  		outptr += 4;
                }
              for (; remain>0; remain--)
              {
                  *outptr = std::tanh(*ptr);
                  ptr++;
                  outptr++;
              }
    }
	
	


#else
    # simple impl

    void multiply(float* x, float *y, float *z, int count) {
    	double s = gemmlowp::real_time_in_seconds();
    		for (int i = 0; i < count; i++)
    			z[i] = x[i] * y[i];
    		double e = gemmlowp::real_time_in_seconds();
    		LOGE("multiply time: %d element wise multiplication %.3g ms\n",count,  (e-s)*1000);
    }

		void Negate(float* x, int count)
	{
		for (int i = 0; i < count; i++)
			x[i] = -x[i];
	}


	void tanh(float *x, int count) {
		for (int i = 0; i < count; i++)
			x[i] = ::std::tanh(x[i]);
	}
	void tanh(float *x, float *y, int count) {
		for (int i = 0; i < count; i++)
			y[i] = ::std::tanh(x[i]);
	}

	void add(float *x, float y, int count) {
		for (int i = 0; i < count; i++)
			x[i] += y;
	}
	void add(float *x, float *y, int count) {
		for (int i = 0; i < count; i++)
			y[i] += x[i];
	}

	void exp(float *x, int count) {
		for (int i = 0; i < count; i++)
			x[i] = ::std::exp(x[i]);
	}
	void reciprocal(float *x, int count) {
		for (int i = 0; i < count; i++)
		{
			if (x[i] != 0)
			{
				x[i] = 1 / x[i];
			}
		}
	}

	float max(float *x, int count) {
		float dMax = -INFINITY;
		for (int i = 0; i < count; i++)
		{
			if (dMax < x[i])
			{
				dMax = x[i];
			}
		}
		return dMax;
	}

	float sum(float *x, int count) {
		float dSum = 0;
		for (int i = 0; i < count; i++)
			dSum += x[i];
		return dSum;
	}

	void divide(float *x, float y, int count) {
		if (y != 0)
		{
			for (int i = 0; i < count; i++)
				x[i] /= y;
		}
	}
	

	void sigmoid(float *x, int count)
	{
	  double s = gemmlowp::real_time_in_seconds();
		Negate(x, count);
		exp(x, count);
		add(x, 1, count);
		reciprocal(x, count);
	   double e = gemmlowp::real_time_in_seconds();
       LOGE("%d elements sigmoid time:%.2g\n", count, (e-s)*1000);
	}


    void softmax(float* x, int count) {
    		// Find the maximum value in the input array.
    		float dmax = max(x, count);
    		add(x, -dmax, count);
    		// Exponentiate all the elements in the array.
    		exp(x, count);
    		// Compute the sum of all exponentiated values.
    		float dsum = sum(x, count);
    		// Divide each element by the sum. This normalizes the array
    		// contents so that they all add up to 1.
    		divide(x, dsum, count);
    	}

#endif
