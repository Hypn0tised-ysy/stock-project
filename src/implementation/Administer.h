#pragma once
#include<vector>
#include<string>
#include"stock.h"
#include<Qstring>
class Administer
{
public://ȫ�����ù��г�Ա�����ڵ��ò鿴
	int adminId;//����Ա��id
	std::string aminName;//����Ա���˺�
	std::string password;//����Ա������
	std::vector<Stock>stocklist;//���ش洢��Ʊ������
	bool addStock(std::string symbol,std::string name,double price);//����Ա��ӹ�Ʊ,����Ϊ��Ʊ���ź͸��ֹ�Ʊ�ĳ�ʼ�۸�
	bool removeStock(int stockId,std::string symbol);//����Աɾ����Ʊ��Ϣ,�����ݿ���ɾ��
	Administer();//
	Administer(int id, std::string name, std::string password);//��Ĭ���βεĹ��캯��
	std::vector<Stock> getStock();//����Ա��Ȩ��ȡ��ǰ�г��Ĺ�Ʊ�б�
};

