SELECT a.商品编号,a.商品名称,SUM(b.数量) AS 订购总数量
FROM GoodsInfo a
JOIN OrderList b ON a.商品编号 = b.商品编号
GROUP BY a.商品编号,a.商品名称
HAVING SUM(b.数量) >= ALL(
	SELECT SUM(c.数量)
	FROM OrderList c
	GROUP BY c.商品编号
)
ORDER BY 订购总数量
