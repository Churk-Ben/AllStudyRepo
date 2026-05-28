SELECT DISTINCT 客户编号,客户姓名
FROM CustomerInfo
WHERE 客户编号 IN (
	SELECT a.客户编号
	FROM OrderList a
	JOIN GoodsInfo b ON a.商品编号 = b.商品编号
	WHERE b.单价 * a.数量 > 30
)
