
##����librdkafka��װ
#####����ָ���������������ѣ�����ָ��offset����
ʹ������

###//���ѻص�	
>void consum_on_msg(void* pInvoker, const MessagePtr& pMsg)
>{
>	
>	printf("date: %s\n",      pMsg->data.c_str());
>	printf("status: %d\n",    pMsg->status);
>	printf("errcode: %d\n",   pMsg->errcode);
>	printf("errmsg: %s\n",    pMsg->errmsg.c_str());
>	printf("partition: %d\n", pMsg->partition);
>	printf("offset: %ld\n",    pMsg->offset);
>	printf("\n");
>
>}

>void test_consumer()
>{
>	mwKafka_Consumer consume(brokers, group_id);
>
>	consume.AddCallBack(CONSUMED, consum_on_msg);//������ѻص�
>	consume.AddCallBack(ONERROR, consum_on_err);//��Ӵ���ص�
>
>	//bool bRet = consume.Subscribe({ { "TEST_08",1,1000},{"TEST_08",2,5000 } },true);//��ʼ����,ָ������ ��>offset
>	bool bRet = consume.Subscribe({ "TEST_08" });//��ʼ����
>	
>	
>	if (!bRet)
>	{
>		printf("%s\n", "Subscribe err");
>	}
>	while (true)
>	{		
>		consume.Poll(500);		//ѭ����������
>	}
>	
>}


###//����
>void producer_on_msg(void* pInvoker, const MessagePtr& pMsg)
>{	
>	/*printf("date: %s\n", pMsg->data.c_str());
>	printf("status: %d\n", pMsg->status);
>	printf("errcode: %d\n", pMsg->errcode);
>	printf("errmsg: %s\n", pMsg->errmsg.c_str());
>	printf("partition: %d\n", pMsg->partition);
>	printf("offset: %ld\n", pMsg->offset);
>	printf("\n");*/
>	
>	printf("%ld\n", ++_offset);
>}

>void sigle_producer()//���߳��ύ
>{	
>	mwKafka_Producer producer(brokers, true);	
>	producer.AddCallBack(DELIVERED, producer_on_msg);
>
>	producer.AddTopics( topic_nameg);
>
>	const char* text = u8"�����½ӵ绰���˴ﰴʵ�ʻ���������ռ���˵�������ºÿ������˴�¬��˹";
>	int pos = 100000;
>	while (pos-- > 0)
>	{		
>		std::string _text = text +  std::to_string(pos);
>		producer.Produce(topic_nameg, _text);
>	}
>	while (true)
>	{
>		producer.Poll(500);
>	}
>}




