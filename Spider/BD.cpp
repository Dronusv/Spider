#include "BD.h"
#include <pqxx/pqxx>



void BD::createBD()
{
	pqxx::transaction tx{ *conn_ptr };
	tx.exec("CREATE TABLE IF NOT EXISTS public.URL("
	"id serial PRIMARY KEY,"
	"url text NOT NULL);");

	tx.exec("CREATE TABLE IF NOT EXISTS public.Word("
		"id serial PRIMARY KEY,"
		"word text NOT NULL);");

	tx.exec("CREATE TABLE IF NOT EXISTS public.CountWord ("
		"id serial PRIMARY KEY,"
		"UrlId INTEGER  REFERENCES public.URL(id),"
		"WordId INTEGER  REFERENCES public.Word(id),"
		"count varchar NOT NULL);");

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
		"VALUES('" + tx.esc(URL)  + "');");
	tx.commit();
}

void BD::insert_word(std::string word)
{
	pqxx::transaction tx{ *conn_ptr };
	tx.exec("INSERT INTO public.Word(word)"
		"VALUES('" + tx.esc(word) + "');");
	tx.commit();
}

void BD::insert_count_word_URL(int count, int id_word, int id_URL)
{
	pqxx::transaction tx{ *conn_ptr };
	tx.exec("INSERT INTO public.CountWord(UrlId,WordId,count)"
		"VALUES('" + std::to_string(id_URL) + "','"+ std::to_string(id_word) +"','" + std::to_string(count) + "');");
	tx.commit();
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


