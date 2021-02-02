// create by wgh
#ifndef _NDN_RTPP_H_
#define _NDN_RTPP_H_

#include <stdint.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <ndn-cxx/face.hpp>
#include <errno.h>
#include <exception>
#include <sys/time.h>

using std::string ;
using namespace ndn ;

// 数据生产者类，用于往网络中发出一个对象
class ndn_rtpp
{
public:
	/*
	 * brief : 构造函数
	 * param : 
	 *		prefix : 生产用于发出数据的前缀
	 *	ret : 
	 */ 
	ndn_rtpp(const string &prefix);
	~ndn_rtpp();
	/*
	 * brief : 启动NDN通信线程 
	 * param : 
	 *	ret : 
	 */ 
	void start() ;
	/*
	 * brief : 向网络中发送一个对象
	 * param : 
	 *		data : 对象缓冲区 
	 *		len : 对象长度 
	 *	ret : 
	 *		int 发出的数据长度
	 */ 
	int sendobj(const char *data, int len) ;
private:
	/*
	 * brief : 接收消费者发来的兴趣包
	 * param : 
	 *		filter : 
	 *		interest : 接收到的兴趣包 
	 *	ret : 
	 */ 
	void onInterest(const InterestFilter& filter, const Interest& interest) ;
	void onRegisterFailed(const Name& prefix, const std::string& reason) ;
	/*
	 * brief : pthread 线程函数
	 * param : 
	 *	ret : 
	 */ 
	static void *run(void *param) ;
private:
	// ; /prefix/timestamp/pkt_seq
	// 当前包序号
	uint32_t pkt_seq ;
	// 生产者用于发数据包的前缀 
	string prefix ;
	// 程序启动时间
	string start_time ;

	// NDN通信接口 
	Face m_face ;
	// NDN密码库
	KeyChain m_keyChain ;
};
#endif 
