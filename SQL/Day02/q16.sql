-- 统计食品类商品的总库存量
SELECT SUM(库存量) AS 总库存量 FROM dbo.GoodsInfo WHERE 商品类别 = '食品类';