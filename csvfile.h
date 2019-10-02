#ifndef CSVFILE_H
#define CSVFILE_H
#include <iostream>
#include <string>
#include <memory>

#include <qvector.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qregularexpression.h>
namespace data {

/**
 * @brief The CsvFile class reads CSV data from a stream and makes it
 * available to the application on a read-only basis.
 *
 * CSV Files contain tabular data in rows and columns according to the
 * format defined by RFC 4180 [https://tools.ietf.org/html/rfc4180].
 * (Ignore the requirement for fields contianign CRLF. We can assume
 * that there are no CRLF in the input files.)
 *
 * The data is accessed through a simple inteface using row and column
 * indices, both of which start at 1 (not zero). The interface also
 * provides access to the header data, i.e., the column names.
 *
 * The CSV data is loaded in the constructor, from an input stream.
 * This allows the data to be read from file or any other source connected
 * to a stream.
 *
 * You will need to implement this class according to the provided interface.
 * There is a set of tests provided in 'testing.cpp' for you to check that
 * your implementation conforms. Be sure to enable testing in 'testingsettings.h'
 * to run the test suite and check your implementation.
 */
class CsvFile
{
public:
    /**
     * @brief CsvFile CsvFile constructor, initialises internal data structures
     * with CSV content from the input stream.
     *
     * Assumes the first row is a header row. If the input contains no
     * content, the CsvFile is considered to have failed to load.
     * @param input the stream from which to read the data
     */
    CsvFile(std::istream &input);

    /**
     * @brief parseRow parse one line of the CSV file
     * @param line a line of (Q)string in csv file
     * @return parsed list of (Q)strings
     */
    QStringList parseRow(QString line);
    
    /**
     * @brief numberOfColumns Returns the number of columns in the CSV file,
     * or -1 if the data failed to load.
     *
     * @return number of columns or -1
     */
    int numberOfColumns();

    /**
     * @brief numberOfRows returns the number of rows in the CSV file,
     * or -1 if the data failed to load.
     *
     * The header row is NOT included in the count of rows.
     *
     * @return number of rows or -1
     */
    int numberOfRows();

    /**
     * @brief replaceAll Replaces "old" in the original string with "newOne"
     * @param original original string
     * @param old the string to be replaced
     * @param newOne new string
     * @return
     */
    QString replaceAll(QString original, QString old, QString newOne);

    /**
     * @brief at Returns the content of the cell at the given row, column.
     *
     * Row indices start at 1, column indices start at 1.
     * Returns an empty string if the CSV file failed to load or if row/column
     * is out of range.
     *
     * @param row the row from which to retrieve the data
     * @param column the column from whcih to retrieve the data
     * @return the cell data at row, column
     */
    std::string at(int row, int column);

    /**
     * @brief headerAt Returns the column name at the given index.
     *
     * Column indices start at 1.
     * Returns an empty string if the CSV file failed to load or if column
     * is out of range.
     *
     * @param column the index of the column
     * @return the column name
     */
    std::string headerAt(int column);

    /**
     * @brief columnIndexOf Returns the column index for the given column name.
     *
     * Returns -1 if the CSV file faild to load.
     * Column indices start at 1.
     *
     * @param columnName the name of the column
     * @return the index of the named column, or -1
     */
    int columnIndexOf(const std::string &columnName);

private:
    std::shared_ptr<QVector<QStringList>> _dataTable; // save the parsed table
    QVector<QVector<bool>> _quotedTable; // store whether each piece is wrapped in double parentheses in a CSV file
    // (usage: field WITHOUT '\\n' replaced with newline, since it is unquoted)
};

} // namespace data

#endif // CSVFILE_H
