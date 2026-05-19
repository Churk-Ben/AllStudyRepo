SELECT AVG(DATEDIFF(YEAR, CustomerInfo.出生日期, GETDATE())) AS 订购商品客户平均年龄
FROM CustomerInfo
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
