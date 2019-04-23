#pragma once
#include <string>
#include <vector>
#include <any>
#include <iguana/json.hpp>
#include "entity.h"
#include "log.hpp"

namespace raftcpp {
	struct address {
		std::string ip;
		int port;
	};
	REFLECTION(address, ip, port);

	struct config {
		address host_addr;
		std::vector<address> peers_addr;
	};
	REFLECTION(config, host_addr, peers_addr);

	struct raft_node {
		std::any udata;  /*һ�㱣��������������������Ϣ����ʹ���߾�����ôʵ������*/

		int next_idx; /*����ÿһ������������Ҫ���͸�������һ����־��Ŀ������ֵ����ʼ��Ϊ�쵼���������ֵ��һ��*/
		int match_idx; /*����ÿһ�����������Ѿ����Ƹ�������־���������ֵ*/

		int flags; /*������ȡֵ�������Ĺ�ϵ 1:�û����и���ͶƱ 2:�û�����ͶƱȨ  3: �û��������µ���־*/

		int id; /*������Ӧ��idֵ�����ÿ̨������ȫ�ֶ���Ψһ��*/
	};

	struct raft_server_private {
		/* ���з������ȽϹ̶���״̬: */

		/* ���������һ��֪�������ںţ���ʼ��Ϊ 0������������ */
		uint64_t current_term = 0;

		/* ��¼�ڵ�ǰ�����ڸ��ĸ�CandidateͶ��Ʊ��
		   */
		int voted_for;
		int voted_count;

		/* ��־��Ŀ����ÿһ����Ŀ����һ���û�״̬��ִ�е�ָ����յ�ʱ�����ں� */
		log_t log;

		/* �䶯�Ƚ�Ƶ���ı���: */

		/* ��֪�������Ѿ����ύ����־��Ŀ������ֵ */
		uint64_t commit_idx;

		/* ���Ӧ�õ�״̬������־��Ŀ����ֵ����ʼ��Ϊ 0������������ */
		uint64_t last_applied_idx;

		/* ����״̬��follower/leader/candidate */
		State state;

		/* ��ʱ�������ں���ÿ��ִ��ʱ�������ֵ */
		int timeout_elapsed;

		//����������raft�ڵ�
		std::vector<raft_node> peer_nodes;

		int election_timeout;
		int election_timeout_rand; //�����ѡ��ʱ��
		int heartbeat_timeout;

		/* ����Leader����Ϣ��û��LeaderʱΪNULL */
		raft_node current_leader;

		///* callbacks���ɵ��ø�raftʵ�ֵĵ�������ʵ�֣�����IO�ͳ־ô洢
		// * ���ɵ�������callback��ʵ�� */
		//raft_cbs_t cb;
		//void* udata;

		/* �Լ�����Ϣ */
		raft_node node;

		/* ��raftʵ��ÿ��ֻ����һ�������������ø��ģ��ñ�����¼raft server
		 * �Ƿ����ڽ������ø���*/
		uint64_t voting_cfg_change_log_idx;
	};
}