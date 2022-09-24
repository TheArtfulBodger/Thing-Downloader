import React from 'react';
import { CounterLabel, UnderlineNav } from '@primer/react';
import { XCircleIcon, IssueClosedIcon, SkipIcon, DownloadIcon } from '@primer/octicons-react';
import RpcComponent from '../RPCComponent';

export default class LinkCountBar extends RpcComponent([['get_n_completed_jobs', 'completed'], ['get_n_skipped_jobs', 'skipped'], ['get_n_failed_jobs', 'failed']]) {
  render () {
    return (<UnderlineNav aria-label="Main">
      <UnderlineNav.Link href="/jobs" selected={this.props.page === 'active'}><DownloadIcon /> Jobs In Progress</UnderlineNav.Link>
      <UnderlineNav.Link href="/jobs/completed" selected={this.props.page === 'completed'}><IssueClosedIcon /> Completed <CounterLabel>{this.state.completed === undefined ? '...' : this.state.completed}</CounterLabel>
      </UnderlineNav.Link>
      <UnderlineNav.Link href="/jobs/skipped" selected={this.props.page === 'skipped'}><SkipIcon /> Skipped <CounterLabel>{this.state.skipped === undefined ? '...' : this.state.skipped}</CounterLabel></UnderlineNav.Link>
      <UnderlineNav.Link href="/jobs/failed" selected={this.props.page === 'failed'}><XCircleIcon /> Failed <CounterLabel>{this.state.failed === undefined ? '...' : this.state.failed}</CounterLabel></UnderlineNav.Link>
    </UnderlineNav>);
  }
}
