SELECT CustomerInfo.客户编号, CustomerInfo.客户姓名, GoodsInfo.*, OrderList.数量
FROM CustomerInfo
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
JOIN GoodsInfo ON OrderList.商品编号 = GoodsInfo.商品编号
WHERE GoodsInfo.单价 >= 50
AND OrderList.数量 >= 2
