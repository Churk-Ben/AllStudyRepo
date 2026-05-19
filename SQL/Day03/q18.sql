SELECT DISTINCT CustomerInfo.所在省市
FROM CustomerInfo
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
JOIN GoodsInfo ON OrderList.商品编号 = GoodsInfo.商品编号
WHERE GoodsInfo.商品类别 = '食品'
