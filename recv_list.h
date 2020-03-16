#ifndef _RECV_LIST_H_
#define _RECV_LIST_H_

enum {RECV_LIST_SZ = 1000} ;

// 接收到的网络包描述
struct pkt_slice_t{
	int nextN ;		// 该网络分片下一个分片序号,用于将包分片组成一个对象
	int len ;		// 网络包数据长度 
	char *data ;	// 网络包数据
} ;

// 帧分片接收队列 
class RecvList
{
public:
	RecvList();
	~RecvList();

	/*
	 * brief : 设置队头指针代表的网络包序号
	 * param : 
	 *		indicate : 网络包初始序号
	 *	ret : 
	 */ 
	void setFrontIndicate(uint32_t indicate) ;
	/*
	 * brief : 往队列尾加入一个网络包
	 * param : 
	 *		pkt : 网络包数据缓冲区
	 *		len : 网络包数据长度
	 *		int : 该对象的下一个分片序号
	 *		seq : 该网络分片序号
	 *	ret : 
	 */ 
	void insertPkt(char *pkt, int len ,int nextN, uint32_t seq) ;

	/*
	 * brief : 判断网络包接收队列尾的几个网络分片能否组成一个对象
	 * param : 
	 *	ret : 
	 *		bool : 返回有或没有
	 */ 
	bool hasFrame() ;
	/*
	 * brief : 将网络包接收队列尾的几个网络分片组合成一个对象 
	 * param : 
	 *		frame : 缓冲区指针
	 *	ret : 
	 *		int : 对象长度
	 */ 
	int getFrame(char **frame) ;
	/*
	 * brief : 丢包处理函数
	 * param : 
	 *		seq : 丢失包序号
	 *	ret : 
	 */ 
	void lossFrame(int seq) ;
	/*
	 * brief : 丢包处理函数,丢包后重新探测最新包序号，并重置接收队列
	 * param : 
	 *	ret : 
	 */ 
	void lossFrame() ;

private:
	/* data */
	// 网络包队列 
	struct pkt_slice_t list[RECV_LIST_SZ] ;
	// 队列头指针
	int front ;
	// 队列尾指针
	int back ;
	// 队列尾指针指向网络包的序号
	uint32_t front_indicate ;	//最左边代表的pkt_seq
};

#endif 
