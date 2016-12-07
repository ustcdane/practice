#coding:utf8
#! /usr/bin/python
import qq_pb2
import sys
import urllib
import httplib
# by Daniel Wang

'''
HTTP POST
'''
def do_post(url, request_body):
    params = request_body.SerializeToString()
    print 'request_body serialize:\n'
    print params
    headers = {"Content-length": len(str(params))}
    
    httpClient = None
    res = None

    try:
        httpClient = httplib.HTTPConnection(url,timeout=2)
        httpClient.request('POST', '/qq.php' , params, headers)
        response = httpClient.getresponse()
        print response.status, response.reason
        res = response.read()
    except Exception, e:
        print e

    finally:
        if httpClient:
            httpClient.close()
            return res

def set_request_body(request_type, sentences_list, request_class):
    request_body = qq_pb2.ClientRequestBody()
    request_body.request_type = request_type
    for sen in sentences_list:
        request_body.sentences.append(sen)
    request_body.request_class = request_class
    return request_body

def print_result(res):
    print "\nrequest_class:"
    print res.request_class
    print "\nServerResponseBody.container_properties:"
    for it in res.container_properties:
        print "%s:\t%s" % (it, res.container_properties[it])

    print "\nServerResponseBody.cards:"
    cnt = 0
    for card in res.cards:
        print "card\t%d:" % (cnt)
        print "template_name:\t%s" % (card.template_name)
        print "is_recommended:\t%s" % (card.is_recommended)
        print "\ncard_properties:"
        for it in card.card_properties:
            print "%s:\t%s" % (it, card.card_properties[it])

        index = 0
        print "\nCarouselUnit:"
        for unit in card.carousel:
            print "CarouselUnit %d:" % (index)
            for it in unit.card_properties:
                print "%s:\t%s" % (it, card.card_properties[it])
            index += 1
        print "\n"
        # subcards ..
        cnt += 1


if __name__ == "__main__":
    '''
    request_body = qq_pb2.ClientRequestBody
    request_body.request_type = qq_pb2.ClientRequestBody.Passive
    request_body.sentences = "China"
    request_body.request_class = "news"
   '''

    #request_body = set_request_body(qq_pb2.ClientRequestBody.Passive, ["China"], "news")
    request_body = set_request_body(qq_pb2.ClientRequestBody.Active, ["王宝强"], "news")

    data = do_post('127.0.0.1:80', request_body)
    output = qq_pb2.ServerResponseBody()
    output.ParseFromString(data)
    #print output
    print_result(output)
