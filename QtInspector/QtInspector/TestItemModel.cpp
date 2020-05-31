#include "TestItemModel.h"
#include <QStringList>
#include <QDebug>


TreeModel::TreeModel(QObject *parent)
	: root(0),QAbstractItemModel(parent)
{
}

TreeModel::~TreeModel()
{
	delete root;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if(!hasIndex(row, column, parent))
		return QModelIndex();

	INode *parentItem;

	if (!parent.isValid())
		if (root)
			parentItem = root;
		else
			parentItem = (INode *)this;
	else
		parentItem = static_cast<INode *>(parent.internalPointer());

	

	INode *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	INode* childItem = static_cast<INode*>(index.internalPointer());
	INode* parentItem = childItem->getParent();

	if (parentItem == root)
		return QModelIndex();


	return createIndex(parentItem->find(childItem), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
	INode *parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		if (!root)
			return 0;
		else
			return root->size();
	else
		parentItem = static_cast<INode*>(parent.internalPointer());


	return parentItem->size();
	
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
	return 2;
}

bool TreeModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role == Qt::EditRole)
	{
		INode* childItem = static_cast<INode*>(index.internalPointer());
		if (childItem)
		{
			childItem->setValue(value.toString());
		}
	}
	return QAbstractItemModel::setData(index,value,role);
}



QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	INode *item = static_cast<INode*>(index.internalPointer());

	if (index.column() == 0)
		return item->getKey();
	else if (index.column() == 1 && item->getType() == dataType::value)
		return static_cast<IValue*>(item)->getValue();

	if (role == Qt::DecorationRole)
	{

	}
	
	return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	if (index.column() == 0)
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;


}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		if (section == 0)
			return tr("Name");
		else
			return tr("Value");

	return QVariant();
}
void TreeModel::reset()
{
	 QAbstractItemModel::beginResetModel();
	 QAbstractItemModel::endResetModel();
}

