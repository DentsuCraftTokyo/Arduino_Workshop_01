
#  Arduino_Workshop_01

Think &amp; Craftで行った「Arduinoワークショップ - デジタルシンセサイザーを作ってみる」のリポジトリです。
## Environments
以下のバージョンで動作確認をしています。

    Mozzi==2.0.1
    Fixmath==1.0.6

## 機材構成
-   ブレッドボード: [ELEGOO 830タイポイント](https://www.amazon.co.jp/Elegoo-830%E3%82%BF%E3%82%A4%E3%83%BC%E3%83%9D%E3%82%A4%E3%83%B3%E3%83%88%E3%83%96%E3%83%AC%E3%83%83%E3%83%89%E3%83%9C%E3%83%BC%E3%83%89-%E3%81%AF%E3%82%93%E3%81%A0%E3%83%AC%E3%82%B9%E3%83%96%E3%83%AC%E3%83%83%E3%83%89%E3%83%9C%E3%83%BC%E3%83%89-Mega2560-Nano%E9%81%A9%E7%94%A8-Arduino/dp/B074C4PRP3) x1
    
-   マイコン: [Waveshare RP2040-Zero](https://www.switch-science.com/products/7886) x1
    
    -   USB-C接続が可能なRaspberry Pi Picoの互換機です。小さいわりにADCピンが4つ使え、ADSRそれぞれに割り当てられるため今回はこちらを採用しました。
        
-   ボリューム: [小型ボリューム 100kΩB](https://akizukidenshi.com/catalog/g/g116468/) x4
    
    -   よくある青い半固定ボリュームは操作性が悪いのでもう少しノブが大きいものを採用しました。ブレッドボードに直挿しできるように、ワークショップ前にピンヘッダを半田付けしておきました。
        
-   タクトスイッチ: タクトスイッチ: [12mm TVGP01-G73BB(黒)](https://akizukidenshi.com/catalog/g/g109826/) x9
    
    -   ドレミファソラシドの8鍵分に加えて、ボリュームが調整する値を変更ためのスイッチが追加で1個あります。これは、ワークショップのパート3でFMのモジュレータを2個直列に繋ぎそれぞれのHarmonicity Ratio, Modulator Indexを変えるためです。また、ボリュームと同様の理由で、操作性の良い大きめのスイッチを採用しています。そのままブレッドボードに載せると列からはみ出してしまうので、ピンの片側2本を上に折り曲げています。
        
-   オーディオジャック: [Youmile TTRS 3.5mm](https://amzn.asia/d/0it5KZMT) x1
    
    -   今回は節約のためにDACを使わず、RP2040の0番ピンを直接tip, ring1に接続することで音を出します。こちらもピンヘッダをワークショップ前に半田付けしています。
        
-   アクティブスピーカー: [ダイソーのミニスピーカー](https://jp.daisonet.com/collections/electricity0208/products/4549131578874) x1
    
    -   税込330円で買えるものとしては十分良く、アンプも内蔵しているのでスピーカーはこちらを採用しました。
        
-   （余力があれば）USB A メスソケット: [KKHMF USBタイプA メスソケット](https://amzn.asia/d/05wqQq71)
    
    -   アクティブスピーカー用の電源を供給するためのUSBソケットです。利用するピンはVBUSとGNDのみとなっています。こちらもピンヘッダをワークショップ前に半田付けしています。ただ**WS本番で人によって給電がうまく行ったり行かなかったりしたので、スピーカーの給電はRP2040経由でやらないで、PCやコンセントからの方が良さそうです。**