SELECT 
CustomerInfo.客户编号,
CustomerInfo.客户姓名,
OrderList.*
FROM CustomerInfo LEFT 
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
WHERE DATEDIFF(YEAR, CustomerInfo.出生日期, GETDATE()) >= 35
