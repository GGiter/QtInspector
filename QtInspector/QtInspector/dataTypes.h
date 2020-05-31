#pragma once
#include <QString>
#include <QVector>

enum class dataType : char
{
	object,
	value,
	array
};

class INode
{
public:
	INode(const QString& k, dataType t,INode* parent = nullptr) : key(k), type(t), parent(parent) {}
	INode() : key(""), type(dataType::value) {}
	QString getKey() const { return key; }
	dataType getType() const { return type; }
	INode* operator[](int index) { return nullptr; }
	INode &INode::operator=(const INode & node)
	{
		this->key = node.getKey();
		this->type = node.getType();
		return *this;
	}
	virtual INode* begin()
	{
		return nullptr;
	}
	virtual INode* end()
	{
		return nullptr;
	}
	virtual int size() { return 0; }
	virtual INode* child(int index) {
		return nullptr;
	}
	INode* getParent() const { return parent; }
	INode* parent;
	virtual int find(INode* node) { return -1; }
protected:
	QString key;
	dataType type;

};


class IValue : public INode
{
public:
	IValue(const QString& k, const QString& v, INode* parent = nullptr) : INode(k,dataType::value,parent), value(v) {}
	QString getValue() const { return value; }
	IValue &IValue::operator=(const IValue & node)
	{
		this->key = node.getKey();
		this->type = node.getType();
		this->value = node.getValue();
		return *this;
	}
	virtual int size() { return 0; }
private:
	QString value;
};

class IArray : public INode
{
public:
	IArray(const QString& k, const QVector<INode*>& v,INode* parent = nullptr) : INode(k,dataType::array,parent), values(v) {}
	IArray(const QString& k, INode* parent = nullptr) : INode(k, dataType::array,parent) {}
	~IArray() { for (INode* value : values)  delete value; }
	void addValue(INode* value) { values.push_back(value); }
	QVector<INode*> getValues() const { return values; }
	INode* operator[](int index) { return values[index]; }
	IArray &IArray::operator=(const IArray & node)
	{
		this->key = node.getKey();
		this->type = node.getType();
		this->values = node.getValues();
		return *this;
	}
	INode* begin()
	{
		if (values.size() == 0)
			return nullptr;
		return values[0];
	}
	INode* end()
	{
		if (values.size() == 0)
			return nullptr;
		return values[values.size() - 1];
	}
	virtual int size() override { return values.size(); }
	virtual INode* child(int index) override {
		return values[index];
	}
	virtual int find(INode* node) override {
		for (int i = 0; i < values.size(); ++i)
		{
			if (values[i] == node)
				return i;
		}
		return -1;
	}
private:
	QVector<INode*> values;
};

class IObject : public INode
{
public:
	IObject(const QString& k, const QVector<INode*>& v, INode* parent = nullptr) : INode(k,dataType::object, parent), values(v) {}
	IObject(const QString& k, INode* parent = nullptr) : INode(k, dataType::object, parent) {}
	~IObject() { for (INode* value : values)  delete value; }
	void addValue(INode* value) { values.push_back(value); }
	QVector<INode*> getValues() const { return values; }
	INode* operator[](int index) { return values[index]; }
	IObject &IObject::operator=(const IObject & node)
	{
		this->key = node.getKey();
		this->type = node.getType();
		this->values = node.getValues();
		return *this;
	}
	virtual INode* begin() override
	{
		if (values.size() == 0)
			return nullptr;
		return values[0];
	}
	virtual INode* end() override
	{
		if (values.size() == 0)
			return nullptr;
		return values[values.size() - 1];
	}
	virtual int size() override { return values.size(); }
	virtual INode* child(int index) override {
		return values[index];
	}
	virtual int find(INode* node) override { 
		for (int i = 0; i < values.size(); ++i)
		{
			if (values[i] == node)
				return i;
		}
		return -1;
	}
private:
	QVector<INode*> values;
};
