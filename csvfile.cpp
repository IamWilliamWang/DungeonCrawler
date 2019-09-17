#include "csvfile.h"

using namespace data;

CsvFile::CsvFile(std::istream &input)
{
	constexpr int bufferLength = 200;
	char buffer[bufferLength]; // 读取时的buffer
	std::shared_ptr<QVector<QStringList>> table = std::make_shared<QVector<QStringList>>(); // 二维String数组
	int columnCount = -1; // 有多少列
	while (input.getline(buffer, bufferLength)) // 读取一行内容
	{
		QString line(buffer);
		line = replaceAll(line, "\"\"", "$$"); // testDoubleQuotesWithinFields补丁：先把合法的""换成$，输出之前再换到"
		QStringList rowList = parseRow(line);
		if (rowList.isEmpty()) // 如果解析失败或者读到的是空的
			return;
		if (columnCount == -1) // 如果读的是表头，记录有多少列
			columnCount = rowList.size();
		if (columnCount < rowList.size()) // 存在extra column，终止读取
			return;
		if (line.count(',') < columnCount - 1) // 如果这一行是完整数据，应该有列数-1个逗号
			return;
		else
		{
			while (rowList.size() < columnCount) // 保证后面的每一行的列数和第一行相同，不同的话插入""
				rowList.append("");
		}
		table->append(rowList); // 插入一行
	}
	if (table->size() != 0)
		_dataTable = table; // 保存二维String
}

QStringList CsvFile::parseRow(QString line)
{
	//return line.split(QRegularExpression(",|\""), QString::SkipEmptyParts); // split(",\"")获得单行内容的每一个部分
	QStringList splitList; // 存放每一块String的List
	int start = 0, end = -1; // 每一块所在的开始和结束位置
	bool quote = false; // 是否处于双引号内
	line.append(','); // 由于最后一个元素如果没有双引号就不会被处理，加逗号使得最后一个也能添加进入
	QVector<bool> quotedList;
	for (int i = 0; i < line.size(); i++)
	{
		QChar ch = line[i]; // 遍历
		if (ch == '"') // 遇到双引号
		{
			if (quote == false) // 如果是开始引号
			{
				if (i > 0 && line[i - 1] == ' ') // 如果开始引号前有空格，终止解析(要求：must load failure for whitespace outside double quotes)
					return QStringList();
				start = i + 1; // 设置下一位置为开始
				quote = true;
			}
			else // 如果是结束引号
			{
				end = i;
				splitList.append(line.mid(start, end - start)); // 插入引号内的String
				quotedList.append(true); // 记录这一部分是由双引号包裹着
				start = i + 1; // 设置开始位置
				quote = false;
			}
		}
		else if (ch == ',' && quote == false) { // 如果遇到逗号而且不在引号里
			if (end != i - 1) // 不是刚插入完就遇到了，
			{
				end = i;
				splitList.append(line.mid(start, end - start)); // 插入内容
				quotedList.append(false); // 记录这一部分不是由双引号包裹着
				start = i + 1;
			}
			else // 是刚插入完就遇到，设置开始位置
				start = i + 1;
		}
	}
	_quotedTable.append(quotedList);
	return splitList;
}

int CsvFile::numberOfColumns()
{
	if (_dataTable == nullptr)
		return -1;
	return _dataTable->at(0).size();
}

int CsvFile::numberOfRows()
{
	if (_dataTable == nullptr)
		return -1;
	return _dataTable->size() - 1;
}

QString CsvFile::replaceAll(QString original, QString old, QString newOne)
{
	if (!original.contains(old)) // nothing should happen
		return original;

	// copy original string to QVecto<QChar>
	QVector<QChar> chars;
	for (QChar ch : original)
		chars.append(ch);
	// find and save indexes.
	QVector<int> fromIndexes;
	int fromIndex = 0, index;
	while ((index = original.indexOf(old, fromIndex)) != -1)
	{
		fromIndexes.append(index);
		fromIndex = index + 1;
	}
	// remove old and insert new one.
	for (auto it = fromIndexes.rbegin(); it != fromIndexes.rend(); it++)
	{
		auto removeStartIndex = *it;
		chars.remove(removeStartIndex, old.size());
		for (auto it2 = newOne.rbegin(); it2 != newOne.rend(); it2++)
			chars.insert(removeStartIndex, *it2);
	}
	return QString(chars.data(), chars.size()); // convert back to QString
}

std::string CsvFile::at(int row, int column)
{
	if (_dataTable == nullptr) // load CSV file failed.
		return "";

	int rowCount = numberOfRows(), columnCount = numberOfColumns(); // 记录_dataTable的行数和列数
	if (row > rowCount || row < 1) // 防止数组越界
		return "";
	if (column > columnCount || column < 1) // 防止数组越界
		return "";

	// 处理并返回结果
	auto rawData = _dataTable->at(row).at(column - 1);
	if (_quotedTable[row][column - 1]) // 如果有引号，替换\\n为\n
	{
		rawData = replaceAll(rawData, "\\n", "\n");
		rawData = replaceAll(rawData, "$$", "\""); // testDoubleQuotesWithinFields补丁
		return rawData.toStdString();
	}
	else { // 如果没有引号，不替换
		return replaceAll(rawData, "$$", "\"").toStdString();
	}
}

std::string CsvFile::headerAt(int column)
{
	if (column > numberOfColumns() || column < 1)
		return "";

	// 处理并返回结果
	auto rawData = _dataTable->at(0).at(column - 1);
	if (_quotedTable[0][column - 1]) // 如果有引号，替换\\n为\n
	{
		rawData = replaceAll(rawData, "\\n", "\n");
		rawData = replaceAll(rawData, "$$", "\""); // testDoubleQuotesWithinFields补丁
		return rawData.toStdString();
	}
	else { // 如果没有引号，不替换\\n
		return replaceAll(rawData, "$$", "\"").toStdString();
	}
}

int CsvFile::columnIndexOf(const std::string &columnName)
{
	if (_dataTable == nullptr)
		return -1;
	int index = _dataTable->at(0).indexOf(QString::fromStdString(columnName));
	return index == -1 ? -1 : index + 1;
}