SELECT CustomerInfo.客户编号, CustomerInfo.客户姓名, OrderList.*
FROM CustomerInfo
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
WHERE CustomerInfo.所在省市 = '江苏南京'
