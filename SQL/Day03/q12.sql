SELECT *
FROM GoodsInfo
WHERE 库存量 > (SELECT AVG(库存量) FROM GoodsInfo)
