SELECT 
GoodsInfo.*,
OrderList.客户编号
FROM GoodsInfo LEFT 
JOIN OrderList ON GoodsInfo.商品编号 = OrderList.商品编号
