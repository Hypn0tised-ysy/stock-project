#pragma once
#include<string>
class My_stock//���ֿ⣬���ڴ洢��Ʊ��Ϣ
{
private:
	std::string symbol;//��Ʊ����
	int sum;//��Ʊ����
public:
	int get_sum();//��ȡ��ǰ��Ʊ���͵�ӵ����
	std::string get_name();//��ȡ��ǰ�Ĺ�Ʊ����
	void setnew_sum(int _sum);//�����µ�����
	My_stock(const std::string _symbol,const int _sum);
};

