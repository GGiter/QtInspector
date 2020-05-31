#include "Delegate.h"
#include <QLineEdit>
#include <QDebug>
#include "dataTypes.h"
TestDelegate::TestDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
}

TestDelegate::~TestDelegate()
{
}

QWidget *TestDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem & option ,
	const QModelIndex &  index ) const
{
	
	QLineEdit *editor = new QLineEdit(parent);

	editor->setClearButtonEnabled(false);

	INode* node = static_cast<INode*>(index.internalPointer());

	if (node)
		editor->setText(node->getValue());

	return editor;
}

void TestDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();

	QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
	lineEdit->setText(value);
}

void TestDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);

	QString value = lineEdit->text();

	model->setData(index, value, Qt::EditRole);
}

void TestDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option,
	const QModelIndex & index ) const
{
	editor->setGeometry(option.rect);
}