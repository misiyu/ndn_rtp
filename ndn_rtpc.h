// create by wgh
#ifndef _NDN_RTPC_H_
#define _NDN_RTPC_H_

#include <stdint.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <ndn-cxx/face.hpp>
#include <errno.h>
#include <exception>
#include <sys/time.h>
#include <queue>

#include "recv_list.h"

using std::string ;
using std::queue ;
using namespace ndn ;

struct frame_t{
	frame_t():len(0),data(0){ }
	~frame_t(){ 
		if(data) free(data) ;
	}
	int len ;
	char *data ;
} ;

/*
 * NDN 消费者
 */ 
class ndn_rtpc
{
public:
	ndn_rtpc(const string &prefix);
	~ndn_rtpc();
	/*
	 * brief : 从缓存中读一个对象 
	 * param : 
	 *		buff : 读出的对象存储到的缓冲区
	 *	ret : 
	 *		int 对象长度
	 */ 
	int readobj(char *buff) ;
private:
	/*
	 * brief : 没用到
	 */ 
	void process_prei(const Interest& interest) ;
	/*
	 * brief : 没用到
	 */ 
	void process_datai(const Interest& interest) ;
	/*
	 * brief : 没用到
	 */ 
	void onInterest(const InterestFilter& filter, const Interest& interest) ;
	void onRegisterFailed(const Name& prefix, const std::string& reason) ;
	/*
	 * brief : 发出拉取数据的兴趣包后，接收到数据 调用该回调函数处理接收到的data包
	 * param : 
	 *		interest : 数据包对应的兴趣包
	 *		data : 接收到的数据包
	 *	ret : 
	 */ 
	void onData(const Interest& interest , const Data& data);
	/*
	 * brief : 发出探测最新视频帧号的兴趣包后，接收到数据 调用该回调函数处理接收到的data包
	 * param : 
	 *		interest : 数据包对应的兴趣包
	 *		data : 接收到的数据包
	 *	ret : 
	 */ 
	void onData_detect(const Interest& interest , const Data& data);
	/*
	 * brief : 拉取数据兴趣包路由错误回调函数
	 * param : 
	 *		interest : 发出的兴趣包 
	 *		data : 接收到的路由错误信息
	 *	ret : 
	 */ 
	void onNack(const Interest& interest, const lp::Nack& nack);
	/*
	 * brief : 探测数据兴趣包路由错误回调函数
	 * param : 
	 *		interest : 发出的兴趣包 
	 *		data : 接收到的路由错误信息
	 *	ret : 
	 */ 
	void onNack_detect(const Interest& interest, const lp::Nack& nack);
	/*
	 * brief : 拉取数据兴趣包兴趣包超时回调函数
	 * param : 
	 *		interest : 发出的兴趣包 
	 *	ret : 
	 */ 
	void onTimeout(const Interest& interest) ;
	/*
	 * brief : 探测数据兴趣包兴趣包超时回调函数
	 * param : 
	 *		interest : 发出的兴趣包 
	 *	ret : 
	 */ 
	void onTimeout_detect(const Interest& interest) ;

	/*
	 * brief : 向数据生产者发送一个探测最新序号的兴趣包
	 * param : 
	 *	ret : 
	 */ 
	void send_detect() ;
	/*
	 * brief : 发拉取数据兴趣包 
	 * param : 
	 *		name : 兴趣包名称
	 *		lifetime : 兴趣包超时时间
	 *	ret : 
	 */ 
	void myExpressInterest(string name, long lifetime) ;
	/*
	 * brief : 发探测兴趣包 
	 * param : 
	 *		name : 兴趣包名称
	 *		lifetime : 兴趣包超时时间
	 *	ret : 
	 */ 
	void myExpressInterest_detect(string name, long lifetime) ;
	/*
	 * brief : 启动NDN通信线程
	 * param : 
	 *		param : 线程参数
	 *	ret : 
	 */ 
	static void *run(void *param) ;

	void getFrame() ;

private:
	/* data */
	// 服务器前缀名
	string prefix ;
	// 当前对象序号
	uint32_t pkt_seq ;
	// 程序启动时间
	string start_time ;

	// 用于帧缓冲区读写同步的静态变量和互斥量
	pthread_mutex_t frame_mutex ;
	pthread_cond_t has_frame ;

	// NDN包数据接收队列
	RecvList recvList ;
	// 接收到的数据对象(数据帧) 队列
	queue<struct frame_t*> myFrameQ ;

	// NDN通信接口
	Face m_face ;
	// NDN密码库
	KeyChain m_keyChain ;

};

#endif 
