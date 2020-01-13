#pragma once
#include "struct.h"

class Producer;
class KAFKA_LIB mwKafka_Producer
{
public:
	//setcb ����Ϊtrue �Զ��������������� ϵͳ�Զ�����
	mwKafka_Producer(const std::string& brokers, bool setcb) : mwKafka_Producer(get_delfault_config(brokers, setcb)) {}
	mwKafka_Producer(const ConfigOption& Config);
	mwKafka_Producer(const ConfigOption& Config, const ConfigOption& Topic_config);

	mwKafka_Producer(const std::string& conf_path);
	~mwKafka_Producer() = default;

public:
	//ֹͣ����
	//�ϲ����˳�ǰ�������,�Ա��õײ����ǿ�ƽ������е���Ϣ���ٷ���KAFKA,���������Ժ�,�ȴ����лص�����
	//timeout_ms>0�ú���������,��ʱ���򷵻�,����֤�������ڼ�һ������Ϣȫ���ʹ�KAFKA,
	//timeout_ms<=0��ʾһ��Ҫ�ȵ���Ϣȫ����ȫ����KAFKA��ŷ���,�����KAFKA����,���ܻᵼ��һֱ�޷�����
	bool Stop(int timeout_ms = 60 * 1000);

	//��ʱ����,�Ա�֪ͨ�ײ�����Ϣץ��Ͷ�ݵ�kafka
	void Poll(int timeout_ms);

	//��kafka������Ϣ,����ָ������
	int Produce(const topic_info_t& _topic, const std::string& _buffer, const std::string& _key = "");

	//�����Ҫ������topic
	//һ�������߿��Ը�����topic������
	bool AddTopics(const std::string& topic_info);
	
	//���brokers
	int AddBrokers(const std::string& brokers);

	//pInvoker:�ϲ���õ���ָ��
	void SetInvoker(void* pInvoker);

	void SetMaxOutQueSize(size_t size);

	//������ϢͶ�ݽ���ص�����
	//pOnDeliveredCb:��ϢͶ�ݻص�����
	void AddCallBack(int _type, DoneCallback pCallBackCb);

	//������־����Ŀ¼
	//��־����Ŀ¼
	//level_��־�ȼ�
	void setLogFile(const std::string& log_path, size_t level_);


private:
	ConfigOption get_delfault_config(const std::string& brokers, bool setcb);
private:
	std::shared_ptr<Producer>_producer;
};



