SELECT OrderList.*
FROM CustomerInfo
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
WHERE CustomerInfo.所在省市 = '江苏南京'
