 
SET default_parallel 1; 
SET pig.noSplitCombination true;
SET job.name 'phone_merge_bigram:Daniel';
SET mapred.fairscheduler.pool ime; 
cell = load '/user/ime/wangdan/phone/bigram/test//cell' as (key1:bytearray, key2:bytearray, tf:double, df:double);
qq = load '/user/ime/wangdan/phone/bigram/test//qq' as (key1:bytearray, key2:bytearray, tf:double, df:double);
merge = cogroup  cell by (key1, key2), qq by (key1, key2);
release = foreach merge generate flatten(group), (float)(0.8*SUM((IsEmpty(cell)?{(0.0)}:cell.tf))+0.3*SUM((IsEmpty(qq)?{(0.0)}:qq.tf)))/(0.8*SUM((IsEmpty(cell)?{(0.0)}:{(1.0)}))+0.3*SUM((IsEmpty(qq)?{(0.0)}:{(1.0)}))), (float)(0.8*SUM((IsEmpty(cell)?{(0.0)}:cell.df))+0.3*SUM((IsEmpty(qq)?{(0.0)}:qq.df)))/(0.8*SUM((IsEmpty(cell)?{(0.0)}:{(1.0)}))+0.3*SUM((IsEmpty(qq)?{(0.0)}:{(1.0)})));
store release into '/user/ime/wangdan/phone/bigram/test/merge.release';
debug = foreach merge generate flatten(group), (float)(0.8*SUM((IsEmpty(cell)?{(0.0)}:cell.tf))+0.3*SUM((IsEmpty(qq)?{(0.0)}:qq.tf)))/(0.8*SUM((IsEmpty(cell)?{(0.0)}:{(1.0)}))+0.3*SUM((IsEmpty(qq)?{(0.0)}:{(1.0)}))), (float)(0.8*SUM((IsEmpty(cell)?{(0.0)}:cell.df))+0.3*SUM((IsEmpty(qq)?{(0.0)}:qq.df)))/(0.8*SUM((IsEmpty(cell)?{(0.0)}:{(1.0)}))+0.3*SUM((IsEmpty(qq)?{(0.0)}:{(1.0)}))), 'cell','0.8', flatten((IsEmpty(cell)?{(0.0,0.0)}:cell.(tf,df))), 'qq','0.3', flatten((IsEmpty(qq)?{(0.0,0.0)}:qq.(tf,df)));
store debug into '/user/ime/wangdan/phone/bigram/test/merge.debug';
