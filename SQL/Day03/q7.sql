SELECT 
CustomerInfo.客户编号,
CustomerInfo.客户姓名,
COUNT(OrderList.客户编号) AS 订单数量
FROM CustomerInfo LEFT 
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
GROUP BY CustomerInfo.客户编号, CustomerInfo.客户姓名
