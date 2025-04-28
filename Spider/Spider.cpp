#include "Spider.h"
#include "regex"
#include "Indexator.h"

Spider::Spider(const std::string& start_url, int max_depth, size_t thread_count) : start_url_(start_url), max_depth_(max_depth), pool_(thread_count),
active_tasks_(0)
{
	curl_global_init(CURL_GLOBAL_DEFAULT); //������ ������ � curl
}

Spider::~Spider()
{
	curl_global_cleanup();           //����� ������ � curl
}

void Spider::connect_to_database(std::string conn_str)
{
	data_base.connectBD(conn_str);
   // data_base.createBD();
}

void Spider::create_data_base()
{
    data_base.createBD();
}



void Spider::Start()
{
    add_url(start_url_, 1);
    // ���� ���������� ���� �����
    while (active_tasks_ > 0) {
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    pool_.stop();
    std::cout << "������� ��������.\n";
}

std::string Spider::get_full_url(const std::string& url, const std::string& base_url)
{
    if (url.find("http://") == 0 || url.find("https://") == 0 || url.find("ftp://") == 0) {
        return url;
    }
    // ���� ������ ���������� � /
    else if (!url.empty() && url.front() == '/') {
        // ������� ��������� ����� � ����� �������� URL
        std::string clean_base = base_url;
        if (clean_base.back() == '/') {
            clean_base.pop_back();
        }
        return clean_base + url;
    }
    // ����� � ������������� ����
    else {
        // ������� ���� � ����� �������� URL
        std::string clean_base = base_url;
        if (clean_base.back() == '/') {
            clean_base.pop_back();  
        }
        return clean_base + "/" + url;
    }
}

std::string Spider::get_base_url(const std::string& url)
{
    size_t protocol_end = url.find("://");
    if (protocol_end == std::string::npos) {
        // ��� ���������, ���������� �������� URL ��� ������ ������
        return url;
    }

    // ���� ��������� ����� ����� ����� ���������
    size_t domain_start = protocol_end + 3; // ����� "://"
    size_t slash_pos = url.find('/', domain_start);

    if (slash_pos == std::string::npos) {
        // ��� ����, ���������� ���� URL ��� �������
        return url;
    }
    else {
        // ���������� ������ �������� � �����
        return url.substr(0, slash_pos);
    }
}

void Spider::add_url(const std::string& url, int depth)
{
    active_tasks_++;
    // ��������� ������ � ��� �������
    pool_.enqueue([this, url, depth]() {
        process_page(url, depth);
        active_tasks_--;
        });
}

void Spider::process_page(const std::string& url, int depth)
{
	//��������� ������
	//�������� ���� � ����� ������������
    std::cout << "���������: " << url << " (������� " << depth << ")\n";

    // ��������� ��������
    std::string content = fetch_page(url);
    std::string HTMLcont = content;
    // ���� ��� ������ �� ��������
    // ���������� ���������� ���������
    std::regex link_regex("<a href=\"(.*?)\"");
    auto links_begin = std::sregex_iterator(content.begin(), content.end(), link_regex);
    auto links_end = std::sregex_iterator();

    Indexator index;
    index.clearSTR(HTMLcont);
    index.lowerCase(HTMLcont);
    index.countwords(HTMLcont);
    index.PrintWordCount();
    index.sendDataBase(data_base, url);
    // ���� �������� ������������ ������� � �� ���� ������
    if (depth >= max_depth_) return;

    for (auto it = links_begin; it != links_end; ++it) {
        std::string link = (*it)[1].str();
        std::string fulllink = get_full_url(link, get_base_url(url));
        // ���������, �� �������� �� ���
        {
            std::lock_guard<std::mutex> lock(visited_mutex_);
            if (visited_.count(fulllink)) continue;
            visited_.insert(fulllink);
        }

        // ��������� ����� ������ ��� ���� ������
       // std::cout << fulllink <<"\n";
        add_url(fulllink, depth + 1);
    }

}

std::string Spider::fetch_page(const std::string& url)
{
	//��������� ����� �� ������
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("�� ������� ���������������� curl");
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // �������������� ���������� ����������
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "MyCrawler/1.0"); // ���������������� �����

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        // ����� ���������� ������ ��� ��������� ����������
        throw std::runtime_error(curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    return response;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t totalSize = size * nmemb;
	std::string* str = (std::string*)userp;
	str->append((char*)contents, totalSize);
	return totalSize;
}
