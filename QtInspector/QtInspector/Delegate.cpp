#include "Delegate.h"
#include <QLineEdit>
#include <QDebug>
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

	return editor;
}

void TestDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();

	QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
	spinBox->setText(value);
}

void TestDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QLineEdit *spinBox = static_cast<QLineEdit*>(editor);

	QString value = spinBox->text();

	model->setData(index, value, Qt::EditRole);
}

void TestDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option,
	const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}