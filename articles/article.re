
= 章タイトル

== Gitとは
== Submoduleとは

プロジェクトAとプロジェクトBの両方で同じライブラリを使いたい！
そのライブラリをメンテナンスするのはプロジェクトCのみなさんだとします。

このときプロジェクトAのリポジトリにも、プロジェクトBのリポジトリにもライブラリのソースコードを直接置いてしまう（プロジェクトのツリーに取り込んでしまうと）と、プロジェクトCのメンバーがライブラリをメンテナンスしたいときに、両方のリポジトリでそれぞれ更新しなければなりません。

Gitのサブモジュールを使うと、プロジェクトCのリポジトリを、別のリポジトリのサブディレクトリとして扱えるようになります。プロジェクトAやプロジェクトBを親（メイン）としたとき、子（サブ）にあたるプロジェクトCのコミットは、親のコミットとは別で管理できます。

== サブモジュールの作り方

まず親を作ります。

//cmd{
メインのリポジトリ（main_project）を作る
$ git init main_project
//}


続いてメインのリポジトリのサブモジュールとして、既に存在している別のリポジトリを追加します。

//cmd{
作ったリポジトリのディレクトリに移動する
$ cd main_project

サブモジュールとして「SubmoduleUpdated」というリポジトリを追加する
$ git submodule add https://github.com/mochikoAsTech/SubmoduleUpdated
//}

今回はサブモジュールとして、本書の原稿リポジトリを追加してみました。@<fn>{url}追加したSubmoduleUpdatedをクローンしてくるため、こんな表示がされたと思います。

//footnote[url][今回はGitHubのURLを指定しましたが、このような絶対のURLに限らず、相対パスでサブモジュールのリポジトリを指定することも可能です。]

//cmd{
$ git submodule add https://github.com/mochikoAsTech/SubmoduleUpdated
Cloning into 'C:/Users/mochikoAsTech/Documents/main_project/SubmoduleUpdated'...
remote: Enumerating objects: 162, done.
remote: Counting objects: 100% (162/162), done.
remote: Compressing objects: 100% (143/143), done.
remote: Total 162 (delta 43), reused 26 (delta 7), pack-reused 0 eceiving objects:  93% (151/162), 308.00 KReceiving objects: 100% (162/162), 308.00 KiB | 604.00 KiB/s
objects: 100% (162/162), 518.33 KiB | 772.00 KiB/s, done.
Resolving deltas: 100% (43/43), done.
//}

サブモジュールを追加するとき、特にディレクトリ名を指定しないと、次のようにリポジトリの名前がそのままディレクトリ名となります。（@<img>{SubmoduleUpdated_1}）

//image[SubmoduleUpdated_1][SubmoduleUpdatedがサブモジュールとして追加された][scale=0.8]{
//}


@<code>{startdns01}




デフォルトでは、このコマンドで指定したリポジトリと同名のディレクトリに、サブプロジェクトのデータが格納されます。他のディレクトリを使いたい場合は、コマンドの末尾にパスを追加してください。

たり、作業中のリポジトリのサブモジュールとして既存のリポジトリを追加します。サブモジュールを新たに追加するには git submodule add コマンドを実行します。追跡したいプロジェクトの URL （絶対・相対のいずれも可）を引数に指定してください。この例では、“DbConnector” というライブラリを追加してみます。


== 親子の関係

このときGitのリポジトリを親、サブモジュールを子だとします。
・サブモジュールのmasterブランチのコミットが　A→B→C　で進んでいる（Cは最新だけど未リリースなやつ）
・親のmasterはBを参照している
この場合、親のmasterで git submodule update したら、サブモジュールはBを引っ張ってくるので、安心だと思っている。

submodule updateとは、「"親が指定している子のコミット"に更新しておくれ」なんだと思っております。

== git pullしただけなのに差分が出た
== git checkoutしただけなのに差分が出た
== Submoduleでgit pullしただけなのに差分が出た
== 正しい差分の無くし方
