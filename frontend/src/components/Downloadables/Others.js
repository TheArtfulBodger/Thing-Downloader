import React from 'react';
import { Client } from 'rpc-websockets';
import { CounterLabel, UnderlineNav } from '@primer/react';
import { XCircleIcon, IssueClosedIcon, SkipIcon} from '@primer/octicons-react';


export default class LinkCountBar extends React.Component {
  tick = null;
  state = { completed: 0, skipped: 0, failed: 0 };
  client = null;

  componentDidMount () {
    this.client = new Client('ws://localhost:9090/rpc');
    this.tick = setInterval(
      async () => {
        const completed  =await this.client.call('get_n_completed_jobs')
        const skipped = await this.client.call('get_n_skipped_jobs')
        const failed =  await this.client.call('get_n_failed_jobs')

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
  <UnderlineNav.Link href="/jobs/completed"><IssueClosedIcon/> Completed <CounterLabel>{this.state.completed}</CounterLabel>
  </UnderlineNav.Link>
  <UnderlineNav.Link href="/jobs/skipped"><SkipIcon/> Skipped <CounterLabel>{this.state.skipped}</CounterLabel></UnderlineNav.Link>
  <UnderlineNav.Link href="/jobs/failed"><XCircleIcon/> Failed <CounterLabel>{this.state.failed}</CounterLabel></UnderlineNav.Link>
</UnderlineNav>

    );
  }
}
