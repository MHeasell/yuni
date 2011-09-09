
#include "dictionary.h"
#include "sqlite/sqlite3.h"
#include "indexes.h"
#include "logs.h"



using namespace Yuni;


namespace Dictionary
{

	AllWords  allWords;

	Yuni::Mutex mutex;



	Yuni::sint64 FindWordID(const Word& word)
	{
		Yuni::MutexLocker locker(mutex);
		const AllWords::const_iterator it = allWords.find(word);
		if (it == allWords.end())
			return -1;
		return it->second;
	}


	void PreloadFromIndexDB()
	{
		Yuni::MutexLocker locker(mutex);
		allWords.clear();
		sqlite3* handle = (sqlite3*) DocIndex::DatabaseHandle();
		if (!handle)
			return;

		char** result;
		int rowCount, colCount;
		if (SQLITE_OK != sqlite3_get_table(handle, "SELECT id,term FROM terms", &result, &rowCount, &colCount, NULL))
			return;

		if (rowCount)
		{
			if (rowCount == 1)
				logs.info() << "Preloading 1 term from the index db";
			else
				logs.info() << "Preloading " << rowCount << " terms from the index db";

			unsigned int y = 2;
			for (unsigned int row = 0; row < (unsigned int) rowCount; ++row)
			{
				const StringAdapter sid  = result[y++];
				const Word term = result[y++];
				allWords[term] = sid.to<sint64>();
			}
		}
		sqlite3_free_table(result);
	}




} // namespace Dictionary