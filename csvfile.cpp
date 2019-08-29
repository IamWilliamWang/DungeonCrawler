#include "csvfile.h"

using namespace data;

CsvFile::CsvFile(std::istream &input)
{
  // TODO: implement the constructor
}

int CsvFile::numberOfColumns() const
{
  // TODO: implement this method. See header for description.
  return -10;
}

int CsvFile::numberOfRows() const
{
  // TODO: implement this method. See header for description.
  return -10;
}

std::string CsvFile::at(int row, int column) const
{
  // TODO: implement this method. See header for description.
  return "not yet implemented";
}

std::string CsvFile::headerAt(int column) const
{
  // TODO: implement this method. See header for description.
  return "not yet implemented";
}

int CsvFile::columnIndexOf(const std::string &columnName) const
{
  // TODO: implement this method. See header for description.
  return -10;
}
