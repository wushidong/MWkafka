#pragma once
#ifndef __KAFKA_HEADER__
#define __KAFKA_HEADER__
#include <string>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <functional>

#define MWKFK_VERSION  "V1.0"
#define MWKFK_VERSION_NUM  20200108

#ifdef KAFKA_LIB
# ifndef KAFKA_LIB
#  define KAFKA_LIB
# endif
#elif defined(KAFKA_DLL) || defined(_WINDLL)
# if defined(KAFKA_EXPORTS) || defined(kafka_EXPORTS)
#  ifndef KAFKA_LIB
#   define KAFKA_LIB __declspec(dllexport)
#  endif
# elif !defined(KAFKA_LIB)
#  define KAFKA_LIB __declspec(dllimport)
# endif
#elif !defined(KAFKA_LIB)
# define KAFKA_LIB
#endif

enum Offset
{
	OFFSET_BEGINNING = -2,
	OFFSET_END = -1,
	OFFSET_STORED = -1000,
	OFFSET_INVALID = -1001
};
enum CALL_BACK_TYPE
{
	CONSUMED = 1,
	OFFSETCOMMIT,
	DELIVERED,
	ONERROR
};
struct topic_info_t
{
	std::string topic;
	int32_t partition;
	int64_t offset;

	topic_info_t(const std::string& topic_name) :topic_info_t(topic_name, -1) {}
	topic_info_t(const std::string& topic_name, int32_t _partition) :topic_info_t(topic_name, _partition, OFFSET_INVALID) {}
	topic_info_t(const std::string& topic_name, int32_t _partition, int64_t _offset) :topic(topic_name), partition(_partition), offset(_offset) {}
};
struct data_message_t
{
	std::string topic;		//��Ϣtopic_name
	std::string data;		//��Ϣ������,��size()����ȡֵ
	std::string key;		//��Ϣ��key,��size()����ȡֵ

	int32_t partition;		//��Ϣ���ڷ���
	int64_t offset;			//��Ϣ���ڷ����ϵ�ƫ����
	int errcode;			//������ 0:�ɹ�       ��0:ʧ��,ԭ���errmsg
	std::string errmsg;		//����������
	int status;				//Producer��Ϣ��Ӧ��Ͷ��״̬ 0:NOT_PERSISTED 1:POSSIBLY_PERSISTED 2:PERSISTED
							//errcode=0&&status=2ʱ��ʾ�ɹ�,����״̬��ʾʧ��	

	int64_t producer_tm_ms;	        //����Ϣ����produce�ӿڵ�ʱ��
	int64_t producer_cb_tm_ms;		//����Ϣ����produce�ص���ʱ��

	int64_t consumer_tm_ms;	        //���ѵ�����Ϣ��ʱ��	
	int64_t commit_offset_tm_ms;	//����Ϣoffset�ύ��ʱ��
	int64_t committed_tm_ms;        //����Ϣoffset�ɹ��ύ��ִ��ʱ��

	int64_t retry_cnt_;

	const data_message_t& operator==(const data_message_t& other)
	{
		this->topic = other.topic;
		this->data = other.data;
		this->key = other.key;

		this->partition = other.partition;
		this->offset = other.offset;
		this->errcode = other.errcode;
		this->errmsg = other.errmsg;
		this->status = other.status;
		this->consumer_tm_ms = other.consumer_tm_ms;
		this->producer_tm_ms = other.producer_tm_ms;
		this->producer_cb_tm_ms = other.producer_cb_tm_ms;
		this->commit_offset_tm_ms = other.commit_offset_tm_ms;
		this->committed_tm_ms = other.committed_tm_ms;
		this->retry_cnt_ = other.retry_cnt_;
		return *this;
	}
};
using MessagePtr = std::shared_ptr<data_message_t>;
using DoneCallback = std::function<void(void* pInvoker, const MessagePtr& cb_msg_ptr)>;

class Option
{
public:
	Option(const std::string& key, const std::string& value) : key_(key), value_(value) {}
	Option(const std::string& key, const char* value) : key_(key), value_(value) {}
	Option(const std::string& key, bool value) : key_(key), value_(value ? "true" : "false") {}

	template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
	Option(const std::string & key, T value) : Option(key, std::to_string(value)) {}
	const std::string& get_key() const { return key_; }
	const std::string& get_value() const { return value_; }
private:
	std::string key_;
	std::string value_;
};
using ConfigOption = std::vector<Option>;
#endif

