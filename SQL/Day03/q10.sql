SELECT 
CustomerInfo.*,
OrderList.商品编号
FROM CustomerInfo LEFT JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
