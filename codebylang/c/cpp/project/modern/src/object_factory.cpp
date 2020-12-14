template <
typename AbstractProduct,
typename IdentifierType,
typename ProductCreator = Functor<AbstractProduct*>,
template <typename ,typename> class FactoryErrorPolicy 
>
class Factory :public FactoryErrorPolicy<IdentifierType,AbstractProduct>{
public:
	bool Register(const IdentifierType& id, ProductCreator creator) {
		//std::make_pair(id, creator)
		return assoc_.insert(AssocMap::value_type(id, creator)).second;
	}

	bool Unregister(const IdentifierType& id) {
		return assoc_.erase(id) == 1;
	}

	AbstractProduct* createObject(cosnt IdentifierType& id) {
		auto iter = assoc_.find(id);
		if (i!=assoc_.end()) {
			//调用注册的creator 产生product
			//所有的product都继承自AbstractProduct 
			return (i->second)();
		}
		// error handle
		OnKnowType(id);
	} 
private:
	typedef std::map<IdentifierType, AbstractProduct> AssocMap;
	AssocMap assoc_;
};


// Clone Factory, 负责对象Clone
// 将每一个class的typeinfo作为key
template <
typename AbstractProduct,
typename ProductCreator = Functor<AbstractProduct*>,
template <typename ,typename> class FactoryErrorPolicy 
>
class CloneFactory :public FactoryErrorPolicy<IdentifierType,AbstractProduct>{
public:
	bool Register(const TypeInfo& type_info, ProductCreator creator) {
		//std::make_pair(id, creator)
		return assoc_.insert(AssocMap::value_type(type_info, creator)).second;
	}

	bool Unregister(const TypeInfo& type_info) {
		return assoc_.erase(type_info) == 1;
	}

	// 传入一个对象的指针,clone对应的对象
	AbstractProduct* createObject(cosnt AbstractProduct* model) {
		// clone model
		// 通过RTTI机制,运行时生成TypeInfo,根据TypeInfo产生对应的product
		TypeInfo type_info = TypeInfo(typeid(*model));
		auto iter = assoc_.find(type_info);
		if (i!=assoc_.end()) {
			//调用注册的creator 产生product
			//所有的product都继承自AbstractProduct 
			return (i->second)();
		}
		// error handle
		OnKnowType(id);
	} 
private:
	typedef std::map<TypeInfo, AbstractProduct> AssocMap;
	AssocMap assoc_;
};
