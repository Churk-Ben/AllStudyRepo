-- 将食品类商品信息按价格降序排列
SELECT * FROM dbo.GoodsInfo WHERE 商品类别 = '食品' ORDER BY 单价 DESC;