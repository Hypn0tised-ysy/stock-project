#include "Administer.h"
#include "../database/database.h"
#include <QVariantList>
extern Database db;
bool Administer::addStock(std::string symbol,std::string name, double price)//����Ա��ӹ�Ʊ,��Ʊ���ź͹ɼ�
{
	std::vector<Stock> tem = db.getStocksList();
	this->stocklist.assign(tem.begin(), tem.end());//�����صĹ�Ʊ���ݸ���
	if (stocklist.empty())//����ֿ�Ϊ��,��ֱ����ӹ�Ʊ
	{
		Stock stock(symbol, price);
		this->stocklist.push_back(stock);
		return db.addStock(QString::fromStdString(symbol), QString::fromStdString(name), price);
	}
	else//����ֿⲻΪ��
	{
		for (auto tem1 : stocklist)
		{
			if (tem1.symbol == symbol)//�����ӵĹ�Ʊ�г��Ѿ����ڵĻ�����ô�޷�������Ӳ���
			{
				return false;
			}
		}
		//��֮���г��в��������ֹ�Ʊ,����ӽ����Ʊ��list�� 
		Stock stock(symbol, price);
		this->stocklist.push_back(stock);
		return db.addStock(QString::fromStdString(symbol), QString::fromStdString(name), price);
	}
	
	
}
bool Administer::removeStock(int stockId,std::string symbol)
{
	std::vector<Stock> tem = db.getStocksList();
	this->stocklist.assign(tem.begin(), tem.end());//�����صĹ�Ʊ���ݸ���
	if (this->stocklist.empty())//�г�û�й�Ʊ�����޷�����ɾ������
	{
		return false;
	}
	else//��Ʊ�г����ڹ�Ʊ�����в���
	{
		for (auto tem1 : stocklist)
		{
			if (tem1.symbol == symbol)//�ҵ���
			{
				return db.removeStock(stockId);
			}			
		}
		return false;//û���ҵ�
	}
	 
}
Administer::Administer()
{

}
Administer::Administer(int id=1, std::string name="110", std::string pass="119")// ���س�ʼ��
{
	this->adminId = id;
	this->aminName = name;
	this->password = pass;
}
std::vector<Stock> Administer::getStock()//����Ա��Ȩ�޻�ȡ��ǰ�г����д��ڵĹ�Ʊ
{
	std::vector<Stock> tem= db.getStocksList();
	this->stocklist.assign(tem.begin(), tem.end());//�����صĹ�Ʊ���ݸ���
	return db.getStocksList();
}