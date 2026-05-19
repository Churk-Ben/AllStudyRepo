SELECT 
GoodsInfo.生产商,
ISNULL(SUM(OrderList.数量), 0) AS 江苏客户订购总数量
FROM GoodsInfo
LEFT JOIN OrderList ON GoodsInfo.商品编号 = OrderList.商品编号
LEFT JOIN CustomerInfo ON OrderList.客户编号 = CustomerInfo.客户编号
WHERE CustomerInfo.所在省市 LIKE '江苏%' OR CustomerInfo.所在省市 IS NULL
GROUP BY GoodsInfo.生产商
ORDER BY 江苏客户订购总数量 DESC
