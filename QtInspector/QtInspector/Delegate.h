#pragma once

#include <QStyledItemDelegate>

class TestDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	TestDelegate(QObject *parent);
	~TestDelegate();

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;

	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const override;

	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;
};
