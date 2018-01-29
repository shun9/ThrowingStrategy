//************************************************/
//* @file  :Node.cpp
//* @brief :親子関係を持つノード
//* @date  :2017/12/26
//* @author:S.Katou
//************************************************/
#include "SL_Node.h"
#include <algorithm>
#include <SL_MacroConstants.h>

using namespace ShunLib;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="childrenSize">最初に確保する子の一覧サイズ</param>
Node::Node(int childrenSize):
	m_parent(nullptr)
{
	//子の領域をあらかじめ確保
	m_children.reserve(childrenSize);

	//ダーティーフラグを下ろす
	ClearDirty();

	//使用している状態にしておく
	m_isEnable = true;
}

/// <summary>
/// デストラクタ
/// </summary>
Node::~Node()
{
	//子も同時に消す
	for (int i = 0; i < (int)m_children.size(); i++){
		SAFE_DELETE(m_children[i]);
	}
}

/// <summary>
/// 基底の初期化
/// ダーティーフラグの処理をしたあと
/// 派生クラスの処理を呼び出す
/// </summary>
void Node::BaseInitialize()
{
	//使用していない状態ならフラグを戻す
	if (!m_isEnable) {
		ClearDirty();
	}

	//処理前ならば派生クラスの処理を行う
	if (!m_isDirty[DIRTY_FLAG::INITIALIZE_FLAG]){
		//初期化処理
		Initialize();

		//フラグを立てる
		m_isDirty[DIRTY_FLAG::INITIALIZE_FLAG] = true;

		//使用している
		m_isEnable = true;

		//子の初期化を行う
		for (int i = 0; i < (int)m_children.size(); i++){
			m_children[i]->BaseInitialize();
		}
	}
}

/// <summary>
/// 基底の更新
/// ダーティーフラグの処理をしたあと
/// 派生クラスの処理を呼び出す
/// </summary>
void Node::BaseUpdate()
{
	//使用していない状態なら何もしない
	if (!IsEnable()) {
		return;
	}

	//処理前ならば派生クラスの処理を行う
	if (!m_isDirty[DIRTY_FLAG::UPDATE_FLAG]){
		//更新処理
		Update();

		//フラグを立てる
		m_isDirty[DIRTY_FLAG::UPDATE_FLAG] = true;

		//描画可能にする
		EnableRender();

		//子の更新を行う
		for (int i = 0; i < (int)m_children.size(); i++){
			m_children[i]->BaseUpdate();
		}
	}
}

/// <summary>
/// 基底の描画
/// ダーティーフラグの処理をしたあと
/// 派生クラスの処理を呼び出す
/// </summary>
void Node::BaseRender()
{
	//使用していない状態なら何もしない
	if (!IsEnable()){
		return;
	}

	//処理前ならば派生クラスの処理を行う
	if (!m_isDirty[DIRTY_FLAG::RENDER_FLAG]){
		//描画処理
		Render();

		//フラグを立てる
		m_isDirty[DIRTY_FLAG::RENDER_FLAG] = true;

		//更新可能にする
		EnableUpdate();

		//子の描画を行う
		for (int i = 0; i < (int)m_children.size(); i++){
			m_children[i]->BaseRender();
		}
	}
}

/// <summary>
/// 基底の終了
/// ダーティーフラグの処理をしたあと
/// 派生クラスの処理を呼び出す
/// </summary>
void Node::BaseFinalize()
{
	//処理前ならば派生クラスの処理を行う
	if (!m_isDirty[DIRTY_FLAG::FINALIZE_FLAG]){
		//終了処理
		Finalize();

		//フラグを立てる
		m_isDirty[DIRTY_FLAG::FINALIZE_FLAG] = true;

		//使用していない状態にする
		m_isEnable = false;

		//子の終了を行う
		for (int i = 0; i < (int)m_children.size(); i++){
			m_children[i]->BaseFinalize();
		}
	}
}

/// <summary>
/// 親の設定
/// </summary>
/// <param name="parent">親</param>
/// <returns>設定出来たらtrue</returns>
bool Node::SetParent(Node* parent)
{
	//親が変化しないなら何もしない
	if (m_parent == parent){
		return false;
	}

	//別の親が存在しているとき
	if (m_parent != nullptr) {
		m_parent->RemoveChild(this);
	}

	//親を設定
	m_parent = parent;
	parent->m_children.push_back(this);

	return true;
}

/// <summary>
/// 子の追加
/// </summary>
/// <param name="child">子</param>
/// <returns>追加出来たらtrue</returns>
bool Node::AddChild(Node* child)
{
	//既に自分の子ならば何もしない
	if (child->Parent() == this){
		return false;
	}

	//別の親が存在したなら親子関係を切り離す
	if (child->Parent() != nullptr){
		child->Parent()->RemoveChild(child);
	}

	//子を追加　親を自身に設定
	m_children.push_back(child);
	child->m_parent = this;
	return true;
}

/// <summary>
/// 子の切り離し
/// </summary>
/// <param name="child">子</param>
/// <returns>切り離しに成功したらtrue</returns>
bool Node::RemoveChild(Node* child)
{
	//自身の子ではないなら何もしない
	if (child->Parent() != this){
		return false;
	}

	//一覧の中から子を探す
	std::vector<Node*>::iterator itr = std::find(m_children.begin(), m_children.end(), child);

	//子が存在したなら切り離す
	if (itr != m_children.end()){
		m_children.erase(itr);
	}

	return true;
}

/// <summary>
/// ビジターを受け入れる
/// </summary>
void Node::Accept(Visitor* visitor){
	//受け入れる
	visitor->Visit(this);

	//子にも訪問させる
	for (Node* child:m_children){
		child->Accept(visitor);
	}
}

/// <summary>
/// ダーティーフラグを初期状態に戻す
/// 初期化　更新　描画　終了を可能な状態にする
/// </summary>
void Node::ClearDirty()
{
	//ダーティーフラグを下ろす
	for (int i = 0; i < DIRTY_FLAG::DIRTY_FLAG_END; i++) {
		m_isDirty[i] = false;
	}
}