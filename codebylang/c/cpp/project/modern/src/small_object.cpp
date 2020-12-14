//管理固定大小block
struct Chunk {
	//如果不在尾部设置标志并检测，if内存越界将覆盖下一块内存的位置，链表就会断开,内存管理失败
	void Init(size_t blockSize, unsigned char blocks) {
		pData = new unsigned char[blockSize * blocks];
		blocksAvail = blocks;
		firstAvailBlock = 0;
		unsigned char*p = pData;
		//空闲block的头部存储下一个空闲块的索引
		//此时空闲块被使用索引链接了起来
		int i=0;
		for(;i!=blocks;p+=blockSize) {
			*p=++i;
		}
	}

	void Release() {
		firstAvailBlock=-1;
		firstAvailBlock=0;
		if(pData) delete[] pData;
	}

	//blockSize没有保存在Chunk层次(更高层次)，因此需要一个参数
	//一次只分配一个块大小
	void* Allocate(size_t blockSize) {
		if (blocksAvail == 0) return nullptr_t;
		//链表头删除
		void *ptr = pData + firstAvailBlock * blockSize;
		blocksAvail--;
		firstAvailBlock = *ptr; //取出区块的下一个区块头部索引
		return *ptr;
	}

	void Dealllocte(void* p, size_t blockSize) {
		unsigned char* ptr= static_casr<unsigned char*>p;
		assert((ptr-pData)%blockSize == 0);
		assert(ptr >= PData);
		//链表头插入
		*ptr = firstAvailBlock;
		firstAvailBlock = (unsigned char)(ptr - pData) / blockSize;
		++blocksAvail;
	}

	char* pData;
	blocksAvail; //可用块数
	firstAvailBlock; //第一个可用块索引
};

//管理chunck
class FixedAllocator {
	void *Allocate() {
		//						    当前Chunk无可用内存,查找新Chunk
		if(allocChk == nullptr_t || allocChk->blocksAvail == 0) {
			bool newflag = true;
			for(auto& chk : Chunks) {
				if (chk->blocksAvail > 0) {
					allocChk = &chk;
					newflag = false;
					break;
				}
			}
			if(newflag) {
				Chunks.push_back(Chunk); 
				Chunk& newChunk = Chunks.back();
				newChunk.Init(blockSize, blockNum);
				allocChk = &newChunk;
				deallocChk = &Chunks.front();
				deallocChkIndex = 0;
			}
		}

		return allocChk->Allocate(blockSize);
	}

	/*!
	  归还策略
	  仅一个指针，需要确定它属于哪个chunk,这是一次线性查找，看内存落入的区域
	  1.缓存区归还 维持一个缓存区，将归还块串在缓存区，而不还给Chunk，分配时优先看这里，适合随机归还模式
	  2.上一次Chunk归还 适用于有规律的批量的，小对象一般呈现这样的特点
			从上一次归还的Chunk向上或下查找
	*/

	bool IsInChunk(Chunk *chk, void* ptr) {
		if (ptr >= chk->pData || ptr < chk->pData + blockNum * blockSize) return true;
		else return false;
	}

	void Dealllocte(void* ptr) {
		if (IsInChunk(deallocChk, ptr)) {
			deallocChk->Dealllocte(ptr, blockSize);
			//chunk为空
			if(deallocChk->blocksAvail == blockNum && Chunks.size() > THRESOLD) {
				//移除
				//释放Chunk
			}
		} else {
			//从dealloChk开始两个方向查找
			//移除
			//释放
			//修改deallocChunk
		}
		assert(0);
	}

private:
	size_t blockSize;
	unsigned char blockNum;
	typedef std::vector<Chunk> Chunks;
	Chunks chks; 
	Chunk *allocChk; //最近使用的Chunk
	Chunk *deallocChk; //最近归还的Chunk,适用于批量/有规律归还
};


//分配任意小对象，通过管理一组 FixedAllocator,若没有匹配的则使用::operator new 
class SmallObjAllocator {
public:
	// 默认chunkSize,小型对象阈值，超过大小则new
	SmallObjAllocator(size_t chunkSize, size_t maxObjSize) {

	}
	/*!
	策略1 pool[i]处理字节大小为i的对象会i的倍数对象
	策略2 某种大小的分配需求至少发生一次此分配 FixedAllocator
		  按照区别大小排序，提高查找效率
		  缓存最近使用的 FixedAllocator
	*/ 
	void *Allocate(size_t numBytes) {
		if(numBytes > maxObjSize) {
			unsigned char* p = new unsigned char[numBytes];
			return p;
		} 
		
		//检查pLastAlloc大小命中
		
		//二分查找pool 
		
		// new 新的Fixallocator并插入 
	}

	void Dealllocte(void *p, size_t size) {
		//大对象直接释放
		if(numBytes > maxObjSize) {
			delete[] p;
		} 
		//
	}
private:
	std::vector<FixedAllocator> pool;
	FixedAllocator* pLastAlloc;
	FixedAllocator pLastDealloc;
};

typedef SingletonHolder<SmallObjAllocator> MyAlloc;
class SmallObject {
public:
	static void *operator new(size_t size) {
		return MyAlloc::Instance().Allocate(size);
	}

	// c++对象调用delete ptr时对象size由编译器负责插入代码计算并提供
	static void operator delete(void *p, size_t size) {
		MyAlloc::Instance().Dealllocte(p,size);
	
	}
	virtual ~SmallObject();
};

/*
 glibc malloc/free
	arean 
		mmap/sbrk向系统申请heap空间后，由arena管理,一个arean管理多个heap
		heap被划分为不同大小的chunk
	bin链表 free的chunk会挂载到不同的bin中，分配时先查找不同的bin
	chunk
		Allocated chunk 
		#小对象分配采用的是不同的固定大小预划分
		fast  16-80B
		small <512B
		large >512B
		#最近使用的Chunk，局部性原理优化
		unsort small和large free后被挂到这里 
		top chunk arena最顶层的chunk,可伸缩大小以适应bin不能满足的内存申请
*/

