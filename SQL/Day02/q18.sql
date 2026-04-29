-- 查询订购了商品的客户总数
SELECT COUNT(DISTINCT 客户编号) AS 订购商品的客户总数 FROM dbo.OrderList;