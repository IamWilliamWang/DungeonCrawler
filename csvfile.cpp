#include "csvfile.h"

using namespace data;

CsvFile::CsvFile(std::istream &input) {
	constexpr int bufferLength = 500;
	char buffer[bufferLength]; // char buffer when reading file
	std::shared_ptr<QVector<QStringList>> table = std::make_shared<QVector<QStringList>>(); // 2D String table
	int columnCount = -1; // number of columns
    while (input.getline(buffer, bufferLength)) { // read one line
		QString line(buffer);
		line = replaceAll(line, "\"\"", "$$"); // Due to testDoubleQuotesWithinFields. Save double " as double $, convert back when reading data
		QStringList rowList = parseRow(line);
        if (rowList.isEmpty()) { // If parsing fails or the read is empty
			return;
        }
        if (columnCount == -1) { // If the read is the header of the table, how many columns are recorded
			columnCount = rowList.size();
        }
        if (columnCount < rowList.size()) { // The extra column exists, terminate the read
			return;
        }
        if (line.count(',') < columnCount - 1) { // If the row is complete, there should be number of columns-1 commas
			return;
        }
		else {
            while (rowList.size() < columnCount) { // Make sure that every subsequent row has the same number of columns as the first row
				rowList.append("");
            }
		}
		table->append(rowList); // Insert a row
	}
    if (table->size() != 0) {
		_dataTable = table; // Save 2D String table
    }
}

QStringList CsvFile::parseRow(QString line) {
	QStringList splitList; // Store-each-string List
	int start = 0, end = -1; // Where each piece begins and ends index
	bool quote = false; // Whether the current state is in double quotes
	line.append(','); // Since the last element is not processed without a double quotation mark, adding a comma allows the last element to be processed
	QVector<bool> quotedList;
    for (int i = 0; i < line.size(); ++i) {
		QChar ch = line[i]; // Traverse
        if (ch == '"') { // Encounter double quotation marks
            if (quote == false) { // If it's the opening quote
                if (i > 0 && line[i - 1] == ' ') { // If there is a space before the beginning quotation mark, the parsing is terminated (testDoubleQuotedFields:must load failure for whitespace outside double quotes)
					return QStringList();
                }
				start = i + 1; // Set the next position to start
				quote = true;
            } else { // If it's closing quotes
				end = i;
				splitList.append(line.mid(start, end - start)); // Insert String in quotes
				quotedList.append(true); // This part of the record is enclosed in double quotation marks
				start = i + 1; // Set start position
				quote = false;
			}
		} else if (ch == ',' && quote == false) { // If have a comma and it's not in quotes
            if (end != i - 1) { // If the closing quote mark is not next to this comma
				end = i;
				splitList.append(line.mid(start, end - start)); // Insert content
				quotedList.append(false); // This part of the record is not enclosed in double quotation marks
				start = i + 1;
            } else { // If the closing quote mark is next to this comma, set start position
				start = i + 1;
            }
		}
	}
	_quotedTable.append(quotedList);
	return splitList;
}

int CsvFile::numberOfColumns() {
    if (_dataTable == nullptr) {
		return -1;
    }
	return _dataTable->at(0).size();
}

int CsvFile::numberOfRows() {
    if (_dataTable == nullptr) {
		return -1;
    }
	return _dataTable->size() - 1;
}

QString CsvFile::replaceAll(QString original, QString old, QString newOne) {
    if (!original.contains(old)) { // nothing should happen
		return original;
    }
	// copy original string to QVecto<QChar>
	QVector<QChar> chars;
    for (QChar ch : original) {
		chars.append(ch);
    }
	// find and save indexes.
	QVector<int> fromIndexes;
	int fromIndex = 0, index;
	while ((index = original.indexOf(old, fromIndex)) != -1) {
		fromIndexes.append(index);
		fromIndex = index + 1;
	}
	// remove old and insert new one.
    for (auto it = fromIndexes.rbegin(); it != fromIndexes.rend(); ++it) {
		auto removeStartIndex = *it;
		chars.remove(removeStartIndex, old.size());
        for (auto it2 = newOne.rbegin(); it2 != newOne.rend(); ++it2) {
			chars.insert(removeStartIndex, *it2);
        }
	}
	return QString(chars.data(), chars.size()); // convert back to QString
}

std::string CsvFile::at(int row, int column) {
    if (_dataTable == nullptr) { // load CSV file failed.
		return "";
    }

    // Record the number of rows and columns of _dataTable
    int rowCount = numberOfRows();
    int columnCount = numberOfColumns();
    if (row > rowCount || row < 1) { // Prevent array overbounds
		return "";
    }
    if (column > columnCount || column < 1) { // Prevent array overbounds
		return "";
    }

	// Process and return the result
	auto rawData = _dataTable->at(row).at(column - 1);
    if (_quotedTable[row][column - 1]) { // If there are quotes, replace \\n with \n
		rawData = replaceAll(rawData, "\\n", "\n");
		rawData = replaceAll(rawData, "$$", "\""); // Due to testDoubleQuotesWithinFields
		return rawData.toStdString();
	} else { // If there are no quotes, no substitution
		return replaceAll(rawData, "$$", "\"").toStdString();
	}
}

std::string CsvFile::headerAt(int column) {
    if (column > numberOfColumns() || column < 1) {
		return "";
    }

	// Process and return the result
	auto rawData = _dataTable->at(0).at(column - 1);
    if (_quotedTable[0][column - 1]) { // If there are quotes, replace \\n with \n
		rawData = replaceAll(rawData, "\\n", "\n");
		rawData = replaceAll(rawData, "$$", "\""); // Due to testDoubleQuotesWithinFields
		return rawData.toStdString();
	} else { // If there are no quotes, do not replace \\n
		return replaceAll(rawData, "$$", "\"").toStdString();
	}
}

int CsvFile::columnIndexOf(const std::string &columnName) {
    if (_dataTable == nullptr) {
		return -1;
    }
	int index = _dataTable->at(0).indexOf(QString::fromStdString(columnName));
	return index == -1 ? -1 : index + 1;
}
