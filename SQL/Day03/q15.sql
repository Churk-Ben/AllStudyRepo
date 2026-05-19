SELECT DISTINCT CustomerInfo.客户编号, CustomerInfo.客户姓名
FROM CustomerInfo
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
WHERE OrderList.付款方式 = '支付宝'
  AND OrderList.送货方式 = '送货上门'
