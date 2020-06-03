#include "Delegate.h"
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>
#include "dataTypes.h"
#include <QStyle>
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
	IValue* node = static_cast<IValue*>(index.internalPointer());
	if(node)
	{
		switch(node->getValueType())
		{
		case valueType::INT:
			{
			QLineEdit *editor = new QLineEdit(parent);

			QRegExp re("/^([+-]?[1-9]\d*|0)$/");
			QRegExpValidator *validator = new QRegExpValidator(re, editor);
			editor->setValidator(validator);
				
			editor->setClearButtonEnabled(false);

			editor->setText(index.data(Qt::EditRole).toString());
		
			return editor;
			}
		case valueType::BOOLEAN:
			{
			QComboBox *editor = new QComboBox(parent);
			editor->addItem("false", false);
			editor->addItem("true", true);
			editor->setCurrentIndex(index.data(Qt::EditRole).toBool());
			return editor;
			}
		case valueType::ENUM:
			{
			
			}
		case valueType::FLOAT:
		{
			QLineEdit *editor = new QLineEdit(parent);

			QRegExp re("^[+-]?([0-9]*[.])?[0-9]+$");
			QRegExpValidator *validator = new QRegExpValidator(re, editor);
			editor->setValidator(validator);

			editor->setClearButtonEnabled(false);

			editor->setText(index.data(Qt::EditRole).toString());

			return editor;
		}
		case valueType::STRING:
		{
			QLineEdit *editor = new QLineEdit(parent);

			editor->setClearButtonEnabled(false);

			editor->setText(index.data(Qt::EditRole).toString());

			return editor;
		}
		}
	}
	return nullptr;
	

}

void TestDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	QVariant value = index.model()->data(index, Qt::EditRole);


	IValue* node = static_cast<IValue*>(index.internalPointer());
	if (node)
	{
		if(node->getValueType() == valueType::BOOLEAN)
		{
			QComboBox* comboBox = static_cast<QComboBox*>(editor);
			comboBox->setCurrentIndex(value.toBool());
			
		}
		else
		{
			QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
			lineEdit->setText(value.toString());
		}

	}

}

void TestDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{

	QVariant value;
	IValue* node = static_cast<IValue*>(index.internalPointer());
	if (node)
	{

		if (node->getValueType() == valueType::BOOLEAN)
		{
			QComboBox *comboBox = static_cast<QComboBox*>(editor);
			value = comboBox->currentData();		
		}
		else
		{
			QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
			value = lineEdit->text();
		}

	}
	
	model->setData(index, value, Qt::EditRole);
}

void TestDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option,
	const QModelIndex & index ) const
{
	editor->setGeometry(option.rect);
}