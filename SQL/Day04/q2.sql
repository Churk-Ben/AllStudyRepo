SELECT
  GoodsInfo.商品编号,
  GoodsInfo.商品名称,
  SUM(ISNULL(OrderList.数量, 0)) AS 总数量,
  SUM(ISNULL(OrderList.数量 * GoodsInfo.单价, 0)) AS 总金额
FROM GoodsInfo
LEFT JOIN OrderList ON GoodsInfo.商品编号 = OrderList.商品编号
GROUP BY GoodsInfo.商品编号, GoodsInfo.商品名称;
