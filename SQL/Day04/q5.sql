SELECT a.商品类别,SUM(b.数量) AS 销量
FROM GoodsInfo a
JOIN OrderList b ON a.商品编号 = b.商品编号
GROUP BY a.商品类别
HAVING SUM(b.数量) >= ALL(
	SELECT SUM(d.数量)
	FROM GoodsInfo c
	JOIN OrderList d ON c.商品编号 = d.商品编号
	GROUP BY c.商品类别
)
