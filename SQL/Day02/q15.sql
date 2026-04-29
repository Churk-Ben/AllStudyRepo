-- 查询订单信息中订购数量的最大值和最小值
SELECT MAX(数量) AS 最大订购数量, MIN(数量) AS 最小订购数量 FROM dbo.OrderList;