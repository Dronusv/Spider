#include "BD.h"
#include <pqxx/pqxx>



void BD::createBD()
{
	pqxx::transaction tx{ *conn_ptr };
	tx.exec("CREATE TABLE IF NOT EXISTS public.URL("
		"id serial PRIMARY KEY,"
		"url text NOT NULL UNIQUE) ;");

	tx.exec("CREATE TABLE IF NOT EXISTS public.Word("
		"id serial PRIMARY KEY,"
		"word text NOT NULL UNIQUE,"
		"constraint word_unique unique(word)); ");

	tx.exec("CREATE TABLE IF NOT EXISTS public.CountWord ("
		"UrlId INTEGER  REFERENCES public.URL(id),"
		"WordId INTEGER  REFERENCES public.Word(id),"
		"count varchar NOT NULL,"
		"constraint pk primary key(WordId, UrlId)); ");

	tx.commit();
}

void BD::connectBD(std::string conn_str)
{
	conn_ptr = new pqxx::connection(conn_str);
}



void BD::insert_URL(std::string URL)
{
	pqxx::transaction tx{ *conn_ptr };
	tx.exec("INSERT INTO public.URL(url)"
		"VALUES('" + tx.esc(URL) + "')"
		"ON CONFLICT (url) DO NOTHING; ");
	tx.commit();
}

void BD::insert_word(std::string word)
{
	pqxx::transaction tx{ *conn_ptr };
	tx.exec("INSERT INTO public.Word(word)"
		"VALUES('" + tx.esc(word) + "')"
		"ON CONFLICT (word) DO NOTHING; ");
	tx.commit();
}

void BD::insert_count_word_URL(int count, int id_word, int id_URL)
{
	pqxx::transaction tx{ *conn_ptr };
	tx.exec("INSERT INTO public.CountWord(UrlId,WordId,count)"
		"VALUES('" + std::to_string(id_URL) + "','"+ std::to_string(id_word) +"','" + std::to_string(count) + "');");
	tx.commit();
}

bool BD::existsWord(const std::string& word)
{
	try {
		pqxx::work txn(*conn_ptr);
		pqxx::result res = txn.exec(
			"SELECT 1 FROM words WHERE слово = " + txn.quote(word) + " LIMIT 1;"
		);
		return res.size() > 0; // true, если есть запись
	}
	catch (const std::exception& e) {
		//std::cerr << "Ошибка при проверке существования слова: " << e.what() << std::endl;
		return false;
	}
}



int BD::get_id_URL(std::string URL)
{
	pqxx::transaction tx{ *conn_ptr };
	int id_URl = tx.query_value<int>("SELECT id FROM public.URL WHERE url = '" + tx.esc(URL) +  + "';");
	return id_URl;
}

int BD::get_id_word(std::string word)
{
	pqxx::transaction tx{ *conn_ptr };
	int id_URl = tx.query_value<int>("SELECT id FROM public.Word WHERE word = '" + tx.esc(word) + +"';");
	return id_URl;
}


