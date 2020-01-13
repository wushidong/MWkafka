#pragma once
#include "struct.h"
class Consumer;
class KAFKA_LIB mwKafka_Consumer
{
public:
	mwKafka_Consumer(const std::string& brokers, const std::string& group_id) : mwKafka_Consumer(get_delfault_config(brokers, group_id), get_topic_delfault_config()) {}
	mwKafka_Consumer(const ConfigOption& Config);
	mwKafka_Consumer(const ConfigOption& Config, const ConfigOption& Topic_config);
	mwKafka_Consumer(const std::string& conf_path);
	~mwKafka_Consumer() = default;
	
public:
	//����ĳһ������topic����Ϣ
	//��ָ����ĳһ��������ĳһ��offset��ʼ����(����ʹ��Ĭ��ֵ)
	//�����ظ�����
	//�� assign=trueʱ����ָ��������������
	bool Subscribe(const std::vector<topic_info_t>& topics, bool assign = false);

	//���ѵ���topic ����ָ����������
	//�� assign=trueʱ����ָ��������������
	//�����ظ�����
	bool Subscribe(const topic_info_t& topics, bool assign = false);

	//ָ��offset�ͷ�������,����Subscribe֮��ʹ��
	bool cosumer_seek(const topic_info_t& _topic_info);

	//ȡ����ǰ���еĶ���
	bool unsubscribe();

	//���topic
	bool AddTopics(const topic_info_t& topic_info, bool assign);

	//�ύƫ����,����kafka������Ϣ�ѱ��ɹ�����(ע��:Ĭ���Ǳ����ֶ��ύ!!!)
	//async,0:sync commit, 1:async commit
	//�ύ��Ľ��,��ͨ��pfunc_on_offsetcommitted����,��δ���øûص�����,�ɲ��ô����ύ���
	void CommitOffset(const MessagePtr& msg_for_commit, int async = 0);

	//��ʱ����,�Ա�֪ͨ�ײ��ÿ��ٴ�kafkaȡ��Ϣ
	//�������е�topic�����з�����Ϣ
	//timeout_ms<=0������֪ͨ,���̷���,>0������,����ֵ:10
	MessagePtr Poll(int timeout_ms = 500);	

	//ֹͣ����(ֹͣ����ǰ,Ҫֹͣһ��kafka�ӿڵ���,���������ѽӿں�commitoffset�ӿ�)
	//�ϲ����˳�ǰ�������,�Ա��õײ����ǿ�ƽ������е���Ϣ���ٷ���KAFKA,���������Ժ�,�ȴ����лص�����	
	void Stop();

	//��ͣĳһ��topic������
	bool Pause(const topic_info_t& topic_info);

	//�ָ�ĳһ��topic������
	bool Resume(const topic_info_t& topic_info);
	
	//�����ύ������max_wait_commit���Ѿ�commit_freq��ʱ��δ�ύ��,�ͻᴥ�������ύ
	void SetOffsetCommitPolicy(size_t max_wait_commit, int commit_freq);

	//���brokers
	int AddBrokers(const std::string& brokers);

	//pInvoker:�ϲ���õ���ָ��
	void SetInvoker(void* pInvoker);

	//������Ϣ���ѽ���ص�����	
	//_type ���ûص���Ϣ��������  CONSUMED ,OFFSETCOMMIT,
	//pConsumeCb:��Ϣ���ѻص�����
	void AddCallBack(int _type, DoneCallback pCallBackCb);

	//������־����Ŀ¼
	//��־����Ŀ¼
	//level_��־�ȼ�
	void setLogFile(const std::string& log_path, size_t level_);

private:
	ConfigOption get_delfault_config(const std::string& brokers, const std::string& group_id);	
	ConfigOption get_topic_delfault_config(Offset offset = Offset::OFFSET_END);// Ĭ�ϴ�ĩβ���ѣ����Ҫ��ͷ���� ����offset = OFFSET_END

private:
	std::shared_ptr<Consumer>_consumer;
};





