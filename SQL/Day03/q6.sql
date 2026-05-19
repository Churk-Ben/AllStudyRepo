SELECT OrderList.*, OrderList.数量 * GoodsInfo.单价 AS 订单金额
FROM OrderList
JOIN GoodsInfo ON OrderList.商品编号 = GoodsInfo.商品编号
