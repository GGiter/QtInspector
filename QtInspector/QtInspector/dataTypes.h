#pragma once
#include <QString>
#include <QVector>

enum class dataType : char
{
	object,
	value,
	array
};

enum class valueType
{
	BOOLEAN,
	FLOAT,
	INT,
	STRING,
	ENUM,
	NUL,
};

class INode
{
public:
	INode(const QString& k, dataType t, valueType c = valueType::NUL, INode* parent = nullptr) : key(k), type(t), valType(c),parent(parent) {}
	INode() : key(""), type(dataType::value), valType(valueType::NUL) {}
	QString getKey() const { return key; }
	dataType getType() const { return type; }
	valueType getValueType() const { return valType; }
	
	virtual void setValue(const QString& v) {}
	virtual QString getValue() const { return ""; }
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
	INode* getParent() const { return parent; }
	INode* parent;
	virtual int find(INode* node) { return -1; }
protected:
	QString key;
	dataType type;
	valueType valType;
};


class IValue : public INode
{
public:
	IValue(const QString& k, const QString& v, valueType c, INode* parent = nullptr) : INode(k,dataType::value,c,parent), value(v) {}
	QString getValue() const override { return value; }
	void setValue(const QString& v) override { value = v; }
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
	IArray(const QString& k, const QVector<INode*>& v,INode* parent = nullptr) : INode(k,dataType::array, valueType::NUL,parent), values(v) {}
	IArray(const QString& k, INode* parent = nullptr) : INode(k, dataType::array, valueType::NUL,parent) {}
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
	INode* begin() override
	{
		if (values.empty())
			return nullptr;
		return values[0];
	}
	INode* end() override
	{
		if (values.empty())
			return nullptr;
		return values[values.size() - 1];
	}
	int size() override { return values.size(); }
	int find(INode* node) override {
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
	IObject(const QString& k, const QVector<INode*>& v, INode* parent = nullptr) : INode(k,dataType::object,valueType::NUL,parent), values(v) {}
	IObject(const QString& k, INode* parent = nullptr) : INode(k, dataType::object, valueType::NUL, parent) {}
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
	INode* begin() override
	{
		if (values.empty())
			return nullptr;
		return values[0];
	}
	INode* end() override
	{
		if (values.empty())
			return nullptr;
		return values[values.size() - 1];
	}
	int size() override { return values.size(); }
	int find(INode* node) override { 
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
