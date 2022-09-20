import React from 'react';
import { Client } from 'rpc-websockets';
import { CounterLabel, UnderlineNav } from '@primer/react';
import { XCircleIcon, IssueClosedIcon, SkipIcon, DownloadIcon } from '@primer/octicons-react';

export default class LinkCountBar extends React.Component {
  tick = null;
  state = { completed: 0, skipped: 0, failed: 0 };
  client = null;

  componentDidMount () {
    this.client = new Client('ws://172.29.2.159:9090/rpc');
    this.tick = setInterval(
      async () => {
        if (!this.client.ready) return;
        const completed = await this.client.call('get_n_completed_jobs');
        const skipped = await this.client.call('get_n_skipped_jobs');
        const failed = await this.client.call('get_n_failed_jobs');

        this.setState({
          completed, skipped, failed
        });
      }
      , 1000);
  } // End componentDidMount

  componentWillUnmont () {
    clearInterval(this.tick);
  }

  render () {
    return (

<UnderlineNav aria-label="Main">
<UnderlineNav.Link href="/jobs" selected={this.props.page === 'active'}><DownloadIcon/> Jobs In Progress</UnderlineNav.Link>
  <UnderlineNav.Link href="/jobs/completed" selected={this.props.page === 'completed'}><IssueClosedIcon/> Completed <CounterLabel>{this.state.completed}</CounterLabel>
  </UnderlineNav.Link>
  <UnderlineNav.Link href="/jobs/skipped" selected={this.props.page === 'skipped'}><SkipIcon/> Skipped <CounterLabel>{this.state.skipped}</CounterLabel></UnderlineNav.Link>
  <UnderlineNav.Link href="/jobs/failed" selected={this.props.page === 'failed'}><XCircleIcon/> Failed <CounterLabel>{this.state.failed}</CounterLabel></UnderlineNav.Link>
</UnderlineNav>

    );
  }
}
