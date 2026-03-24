// 随机背景图片选择器
(function() {
    // 图像URL列表
    const imageUrls = [
        "https://images.unsplash.com/photo-1506905925346-21bda4d32df4?w=1920&h=1080&fit=crop",
        "https://images.unsplash.com/photo-1441974231531-c6227db76b6e?w=1920&h=1080&fit=crop",
        "https://images.unsplash.com/photo-1472214103451-9374bd1c798e?w=1920&h=1080&fit=crop",
        "https://images.unsplash.com/photo-1501594907352-04cda38ebc29?w=1920&h=1080&fit=crop",
        "https://images.unsplash.com/photo-1518837695005-2083093ee35b?w=1920&h=1080&fit=crop",
        "https://images.unsplash.com/photo-1506905925346-21bda4d32df4?w=1920&h=1080&fit=crop",
        "https://images.unsplash.com/photo-1469474968028-56623f02e42e?w=1920&h=1080&fit=crop",
        "https://images.unsplash.com/photo-1426604966848-d7adac402bff?w=1920&h=1080&fit=crop"
    ];

    // 从列表中随机选择一个URL
    function getRandomImageUrl() {
        const randomIndex = Math.floor(Math.random() * imageUrls.length);
        return imageUrls[randomIndex];
    }

    // 设置CSS变量
    function setRandomBackground() {
        const randomUrl = getRandomImageUrl();
        const root = document.documentElement;
        root.style.setProperty('--bg-img', `url("${randomUrl}")`);
        
        console.log(`已设置随机背景图片: ${randomUrl}`);
    }

    // 页面加载完成后设置随机背景
    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', setRandomBackground);
    } else {
        setRandomBackground();
    }

    // 可选：添加一个函数来手动刷新背景
    window.refreshRandomBackground = function() {
        setRandomBackground();
    };

})();